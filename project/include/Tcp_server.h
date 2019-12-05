//
// Created by andrey on 04.12.2019.
//

#ifndef K_ON_TCP_SERVER_H
#define K_ON_TCP_SERVER_H

#include <boost/asio.hpp>
#include <iostream>

#define READ_UNTIL_DELIM "\n"

class Tcp_server {
public:
    Tcp_server(unsigned short port);
    void start_server();

private:
    unsigned short port_;
    boost::asio::io_service service_;
    boost::asio::ip::tcp::acceptor acceptor_;

private:
    void on_accept(boost::asio::ip::tcp::socket sock);
    std::string to_string(boost::asio::streambuf &buf);
    virtual std::string handle_request(const std::string &request);  // Если не переопределить, то возвращает request
};


#endif  // K_ON_TCP_SERVER_H
