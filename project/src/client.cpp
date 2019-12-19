#include <iostream>

#include "client.h"
//#include "tcp_client.h"
#include "boost/bind.hpp"
#include <boost/beast/http/parser.hpp>
#include <boost/beast/http.hpp>
#include <fstream>
#include <strstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <regex>

void Client::read() {
    try {
        m_Sock.async_read_some(
                boost::asio::buffer(m_Buf),
                boost::bind(&Client::handle_read, shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    }
    catch (boost::system::system_error const &e)
    {
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
    p.put(boost::asio::buffer(m_Buf), er);
    memset(m_Buf,'\0',1024);
    //std::string str = p.release().at("Cookie").to_string();
    //std::cerr<<str.substr(str.find("sessionid"))<<std::endl;
    //std::cerr<<p.release().target().to_string()<<std::endl;

    boost::property_tree::ptree response;
    std::stringstream answer_from_user_server;

    boost::property_tree::write_json(answer_from_user_server,response);


    /*TcpClient tcp_client;
    tcp_client.connect("0.0.0.0", "7777");
    std::string request = p.release().target().to_string();
    tcp_client.write(request,str.substr(str.find("sessionid")));
    std::string answer_from_user_server = tcp_client.read();
    boost::property_tree::write_json(answer_from_user_server,response);
    tcp_client.close_connection();*/

    std::stringstream response_stream;
    std::string code_answer = "HTTP/1.1 200 OK\r\n";
    std::string set_cook;
    std::string user_info = "OLEG";
    std::string data_info = "SONG123\n";
    /*if (answer_from_user_server == "Wrong request")
    {
        code_answer= "HTTP/1.1 400 Bad Request\r\n";
        answer_from_user_server = "Bad Request";
    }*/
    /*else if (answer_from_user_server == "Wrong param")
    {
        code_answer= "HTTP/1.1 404 Not Found\r\n";
        answer_from_user_server = "Not Found";
    }
     if response.get()_child("session") != ""
     {
        set_cook = "Set-Cookie: sessionid=" + response.get()_child("session"); ""
     }
     user_info = response.get_child("user")
     data_info = response.get_child("user")
     std::string str;
     for (auto it:data_info)
     {
        str = str + "+"<a href='" + it.get_children("id")+"'>"+it.get_children("name")+
        it.get_children("duration")+"</a> <a href='"+it.get_children("id")+"'> Like </a> \n ";
     }
     */
    std::string html = parse_html("/Users/elenaelizarova/CLionProjects/k-on/project/index.html",
            user_info,data_info+
                   "SONGA2\n");
    response_stream << code_answer
                    << "Content-Length:"<< html.size() <<"\r\n\r\n"
                    << set_cook
                    << html;

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

std::string Client::parse_html(std::string html_way,std::string user_info,std::string data_info) {

    std::string line;
    std::stringstream buffer;
    std::stringstream buffer_check;
    std::ifstream in(html_way); //// окрываем файл для чтения
    if (in.is_open()) {
        buffer << in.rdbuf();
    }
    in.close();
    line = std ::regex_replace(buffer.str(),std::regex("\\$user"),user_info);
    line = std ::regex_replace(line,std::regex("\\$data"),"<a href='/song/1'>"+data_info+"</a>");
    return line;
}
