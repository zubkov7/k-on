//
// Created by andrey on 07.12.2019.
//
#include <iostream>

#include "client.h"
#include "tcp_client.h"
#include "manager.h"
#include "boost/bind.hpp"
#include <boost/beast/http/parser.hpp>
#include <boost/beast/http.hpp>

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
    memset(m_Buf, '\0', 1024);
    std::stringstream response_stream;
    std::string request = p.release().target().to_string();

    Manager manager;
    std::string answer_from_user_server = manager.handle_request(request, "516234bd2cb5a395e13958734e03ad3311c1693440c1ba997bcc945b434bf6");

    response_stream << "HTTP/1.1 200 OK\r\n"
                    << "Content-Length: 500\r\n\r\n"
                    << "<!DOCTYPE html>\n"
                    << "<html lang=\"en\">\n"
                    << "<head>\n"
                    << "<meta charset=\"UTF-8\">\n"
                    << "<title>Title</title>\n"
                    << "</head>\n"
                    << "<body>\n"
                    << "<h3>"
                    << answer_from_user_server
                    << "</h3>\n"
                    << "</body>\n"
                    << "</html>";

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