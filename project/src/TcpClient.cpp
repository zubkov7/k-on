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
    if (socket_.is_open()) {
        socket_.close();
    }
}

std::string TcpClient::to_string(boost::asio::streambuf &buf) {
    std::ostringstream tmp;
    tmp << &buf;
    return tmp.str();
}

void TcpClient::close_connection() {
    if (socket_.is_open()) {
        socket_.close();
    }
}

void TcpClient::connect(char *host, char *port) {
    this->host_ = std::string(host);
    this->port_ = boost::lexical_cast<unsigned short>(port);

    try {
        boost::asio::connect(this->socket_, this->resolver_.resolve({host, port}));
    }
    catch (boost::system::system_error const &e) {
        if (e.code() == boost::asio::error::connection_refused) {
            std::cout << "Unable to connect to server " << host << ":" << port << std::endl;
        } else {
            boost::throw_exception(e);
        }
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void TcpClient::write(const std::string &message) {
    boost::asio::streambuf answer;
    std::ostream out(&answer);
    out << message << std::endl;
    try {
        boost::asio::write(this->socket_, answer);
    }
    catch (boost::system::system_error const &e) {
        if (e.code() == boost::asio::error::bad_descriptor || e.code() == boost::asio::error::broken_pipe) {
            std::cout << "The connection to the server is closed\n";
        } else {
            boost::throw_exception(e);
        }
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

std::string TcpClient::read() {
    boost::asio::streambuf received_data;

    try {
        boost::asio::read_until(this->socket_, received_data, READ_UNTIL_DELIM);
    }
    catch (boost::system::system_error const &e) {
        if (e.code() == boost::asio::error::bad_descriptor || e.code() == boost::asio::error::not_connected) {
            std::cout << "The connection to the server is closed\n";
        } else if (e.code() == boost::asio::error::eof) {
            std::cout << "Server closed connection\n";
        } else {
            boost::throw_exception(e);
        }
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    std::string received_data_str = this->to_string(received_data);
    return received_data_str;
}
