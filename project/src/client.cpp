#include <iostream>
#include <boost/bind.hpp>
#include <boost/beast/http/parser.hpp>
#include <boost/beast/http.hpp>
#include <fstream>
#include <strstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <regex>

//#include "manager.h"
#include "client.h"
//#include "json.h"

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

    //std::cout << m_Buf << std::endl;


    std::string url = p.release().target().to_string();  // url
    boost::beast::http::request_parser<boost::beast::http::string_body> p_tmp;
    p_tmp.put(boost::asio::buffer(str_buf), er);
    std::string tmp_session;
    std::string session;  // сессия

    memset(m_Buf, '\0', 1024);
    try {
        tmp_session = p_tmp.release().at("Cookie").to_string();
        //std::cout << "tmp session: " << tmp_session << std::endl;
        session = tmp_session.substr(tmp_session.find("=") + 1);  // сессия
    }
    catch (std::out_of_range &e) {
        std::cout << e.what() << std::endl;
        session = "";
    }

    //std::cout << "session: " << session << std::endl;


    //Manager manager;
    //std::string answer_from_manager = manager.handle_request(url, session);

    //boost::property_tree::ptree response = parse_to_json(answer_from_manager);
    boost::property_tree::ptree response;
    std::stringstream answer_from_user_server;
    boost::property_tree::write_json(answer_from_user_server, response);
    int n = 10;
    response.add("size", n);
    response.add("status", 200);
    response.add("songs", "");
    auto bb=response.get_child("songs");
    for (int i=0;i<n;i++)
    {
        bb.add(std::to_string(i),"123");
        bb.get_child(std::to_string(i)).add("name","name"+std::to_string(i));
        bb.get_child(std::to_string(i)).add("id",i);
        bb.get_child(std::to_string(i)).add("duration",i*100);
    }
    int status = response.get<int>("status");

    std::stringstream response_stream;

    if (status == 500) {  // Внутренняя ошибка сервера
        std::string html = parse_html("../index.html", "", response.get<std::string>("message"));
        response_stream << "HTTP/1.1 500 Internal Server Error\r\n"
                        << "Content-Length:"
                        << html.size()
                        << "\r\n\r\n"
                        << html;
    } else if (status == 503) {  // Какой-то из сервисов недоступен
        std::string html = parse_html("../index.html", "", response.get<std::string>("message"));
        response_stream << "HTTP/1.1 503 Service Unavailable\r\n"
                        << "Content-Length:"
                        << html.size()
                        << "\r\n\r\n"
                        << html;
    } else if (status == 400) {  // Неправильный запрос
        std::string html = parse_html("../index.html", "", response.get<std::string>("message"));
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

        std:: string songs = json_to_songs(bb);



        std::string html = parse_html("/Users/elenaelizarova/CLionProjects/k-on/project/index.html", login,songs);
        //stringify_json(response));
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
    boost::system::error_code erro;
    m_Sock.close(erro);
    std::cout << erro.message();
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
    } else if (user_info == "sign_up") {
        line = std::regex_replace(buffer.str(), std::regex("\\$root"), "signup");

    } else {
        line = std::regex_replace(buffer.str(), std::regex("\\$user"), user_info);
        line = std::regex_replace(line, std::regex("\\$data"), data_info);
    }
    return line;
}

std::string Client::json_to_songs(boost::property_tree::ptree& response) {
    //auto bb=response.get_child("songs");
    std::string str;
    std::string buf_str;
    size_t min =0;
    size_t sec =0;
    for (auto it:response)
    {
        buf_str = it.second.get_child("duration").data().c_str();
        min = std::stoi(buf_str) / 60 ;
        sec = std::stoi(buf_str) - min*60 ;
        str = str + "<div> <a href='/similarsong?song_id=" + it.second.get_child("id").data().c_str() + "'>" +
              it.second.get_child("name").data().c_str() + "</a> Duration:" +
              std::to_string(min) + ":" + std::to_string(sec) +
              + "<a href='/like?song_id=" + it.second.get_child("id").data().c_str() + "&value=1' > Like </a>" +
              "<a href='/listen?song_id=" + it.second.get_child("id").data().c_str() + "'> Listen </a></div>" +
              "\n";
    }

    return str;
}

//        for (auto it : response) {
//            str = str + "<div><a href='/similarsong?song_id=1" +
//                  "Song Name</a> <a href=/like?song_id=1&value=1" +
//                  "Like</a> <a href=/listen?song_id=1>" +
//                  "Listen </a> </div> \n ";
//        }