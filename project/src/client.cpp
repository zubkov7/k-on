#include <iostream>
#include <boost/bind.hpp>
#include <boost/beast/http/parser.hpp>
#include <boost/beast/http.hpp>
#include <fstream>
#include <strstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <regex>

#include "manager.h"
#include "client.h"
#include "json.h"

void Client::read() {
    try {
        m_Sock.async_read_some(
                boost::asio::buffer(m_Buf),
                boost::bind(&Client::handle_read, shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    }
    catch (boost::system::system_error const &e) {
        if (e.code() == boost::asio::error::eof) {  // Клиент закрыл соединение
            std::cout << "-client: Connection closed by peer\n";
            this->sock().close();
        } else {
            boost::throw_exception(e);
        }
    }
}

void Client::handle_read(const boost::system::error_code &e,
                         std::size_t bytes_transferred) {
    if (e == boost::asio::error::eof) {
        std::cout << "-client: " << m_Sock.remote_endpoint().address().to_string()
                  << std::endl;
    }
    if (e)
        return;

    std::cout << "read: " << bytes_transferred << " bytes" << std::endl;
    std::cout << "read thread is " << pthread_self() << std::endl;


    boost::beast::http::request_parser<boost::beast::http::string_body> p;
    boost::beast::error_code er;
    std::string str_buf(m_Buf);
    p.put(boost::asio::buffer(str_buf), er);

    std::cout << m_Buf << std::endl;

    std::stringstream response_stream;
    std::string url = p.release().target().to_string();  // url
    if (url == "/login" || url == "/signup") {
        std::string html = parse_html("../form.html", url.erase(0, 1), "");
        response_stream << "HTTP/1.1 200 OK\r\n"
                        << "Content-Length:"
                        << html.size()
                        << "\r\n\r\n"
                        << html;
    } else {
        boost::beast::http::request_parser<boost::beast::http::string_body> p_tmp;
        p_tmp.put(boost::asio::buffer(str_buf), er);
        std::string tmp_session;
        std::string session;  // сессия

        memset(m_Buf, '\0', 1024);
        try {
            tmp_session = p_tmp.release().at("Cookie").to_string();
            std::cout << "tmp session: " << tmp_session << std::endl;
            session = tmp_session.substr(tmp_session.find("=") + 1);  // сессия
        }
        catch (std::out_of_range &e) {
            std::cout << e.what() << std::endl;
            session = "";
        }

        std::cout << "session: " << session << std::endl;


        Manager manager;
        std::string answer_from_manager = manager.handle_request(url, session);

        boost::property_tree::ptree response = parse_to_json(answer_from_manager);

        int status = response.get<int>("status");

        if (status == 500) {  // Внутренняя ошибка сервера
            std::string html = parse_html("../error.html", "", response.get<std::string>("message"));
            response_stream << "HTTP/1.1 500 Internal Server Error\r\n"
                            << "Content-Length:"
                            << html.size()
                            << "\r\n\r\n"
                            << html;

        } else if (status == 503) {  // Какой-то из сервисов недоступен
            std::string html = parse_html("../error.html", "", response.get<std::string>("message"));
            response_stream << "HTTP/1.1 503 Service Unavailable\r\n"
                            << "Content-Length:"
                            << html.size()
                            << "\r\n\r\n"
                            << html;
        } else if (status == 400) {  // Неправильный запрос
            std::string html = parse_html("../error.html", "", response.get<std::string>("message"));
            response_stream << "HTTP/1.1 400 Bad Request\r\n"
                            << "Content-Length:"
                            << html.size()
                            << "\r\n\r\n"
                            << html;
        } else if (status == 403) {  // Не залогинен нужно перевести на страницу логина
            std::string html = parse_html("../form.html", "login", "");
            response_stream << "HTTP/1.1 403 Forbidden\r\n"
                            << "Content-Length:"
                            << html.size()
                            << "\r\n\r\n"
                            << html;
        } else if (status == 303) {  // Не залогинен нужно перевести на страницу логина
            std::string html = parse_html("../form.html", "login", "");
            response_stream << "HTTP/1.1 200 OK\r\n"
                            << "Content-Length:"
                            << html.size()
                            << "\r\n\r\n"
                            << html;
        } else if (status == 401) {  // Неправильный логин или пароль
            std::string html = parse_html("../index.html", "", response.get<std::string>("message"));
            response_stream << "HTTP/1.1 401 Unauthorized\r\n"
                            << "Content-Length:"
                            << html.size()
                            << "\r\n\r\n"
                            << html;
        } else if (status == 200) {  // Вернуть ответ
            std::string login;
            if (response.find("login") == response.not_found()) {
                login = "some login";
            } else {
                login = response.get<std::string>("login");
            }

            std::string html = parse_html("../index.html", login, json_to_songs(response));
            response_stream << "HTTP/1.1 200 OK\r\n"
                            << "Content-Length:"
                            << html.size()
                            << "\r\nSet-Cookie: sessionid=";

            if (response.find("session") == response.not_found()) {
                response_stream << session;
            } else {
                response_stream << response.get<std::string>("session");
            }
            response_stream << "\r\n\r\n"
                            << html;
        }
    }
    int k = 0;
    k = snprintf(m_SendBuf + k, sizeof(m_SendBuf) - k,
                 "%s", response_stream.str().c_str());

    m_Sock.async_write_some(
            boost::asio::buffer(m_SendBuf),
            [self = shared_from_this()](const boost::system::error_code &e,
                                        std::size_t bytes_transferred) -> void {
                // После того, как запишем ответ, можно снова читать
                self->read();
            });
}

std::string Client::parse_html(std::string html_way, std::string user_info, std::string data_info) {

    std::string line;
    std::stringstream buffer;
    std::stringstream buffer_check;
    std::ifstream in(html_way); //// окрываем файл для чтения
    if (in.is_open()) {
        buffer << in.rdbuf();
    }
    in.close();
    if (user_info == "login") {
        line = std::regex_replace(buffer.str(), std::regex("\\$root"), "login");
        line = std::regex_replace(line, std::regex("\\$another"), "<div><a href='/signup'>signup</a></div>");
    } else if (user_info == "signup") {
        line = std::regex_replace(buffer.str(), std::regex("\\$root"), "signup");
        line = std::regex_replace(line, std::regex("\\$another"), "<div><a href='/login'>login</a></div>");

    } else {
        line = std::regex_replace(buffer.str(), std::regex("\\$user"), user_info);
        line = std::regex_replace(line, std::regex("\\$data"), data_info);
    }
    return line;
}


std::string Client::json_to_songs(boost::property_tree::ptree &response) {
    auto songs_array = response.get_child("songs");

    std::string str;
    for (auto song : songs_array) {
        int duration = song.second.get<int>("duration");
        int minutes = duration / 60;
        int seconds_val = duration - minutes * 60;
        std::string seconds = std::to_string(seconds_val);
        if (seconds_val < 10) {
            seconds = "0" + seconds;
        }
        str += "<div> <a href='/similarsong?song_id=" + std::to_string(song.second.get<int>("id")) + "'>" +
               song.second.get<std::string>("author") + " - " +
               song.second.get<std::string>("name") + "</a>  " +
               std::to_string(minutes) + ":" + seconds +
               +"<a href='/like?song_id=" + std::to_string(song.second.get<int>("id")) + "&like=1' > Like </a>" +
               "<a href='/listen?song_id=" + std::to_string(song.second.get<int>("id")) + "'> Listen </a></div>" +
               "\n";
    }

    return str;
}