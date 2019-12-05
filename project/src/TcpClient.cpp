//
// Created by andrey on 04.12.2019.
//

#include <boost/lexical_cast.hpp>
#include <iostream>

#include "TcpClient.h"

TcpClient::TcpClient() :
    socket_(boost::asio::ip::tcp::socket(this->service_)),
    resolver_(boost::asio::ip::tcp::resolver(this->service_)) {}

TcpClient::~TcpClient() {
    socket_.close();
}

std::string TcpClient::to_string(boost::asio::streambuf &buf) {
    std::ostringstream tmp;
    tmp << &buf;
    return tmp.str();
}

void TcpClient::close_connection() {
    socket_.close();
}

void TcpClient::connect(char *host, char *port) {
    this->host_ = std::string(host);
    this->port_ = boost::lexical_cast<unsigned short>(port);

    boost::asio::connect(this->socket_, this->resolver_.resolve({host, port}));
}

void TcpClient::write(const std::string &message) {
    boost::asio::streambuf answer;
    std::ostream out(&answer);
    out << message << std::endl;
    boost::asio::write(this->socket_, answer);
}

std::string TcpClient::read() {
    boost::asio::streambuf received_data;
    boost::asio::read_until(this->socket_, received_data, READ_UNTIL_DELIM);

    std::string received_data_str = this->to_string(received_data);
    return received_data_str;
}
