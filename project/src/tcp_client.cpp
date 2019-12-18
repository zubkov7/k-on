//
// Created by andrey on 04.12.2019.
//

#include <boost/lexical_cast.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <iostream>

#include "tcp_client.h"

TcpClient::TcpClient() :
        socket_(boost::asio::ip::tcp::socket(this->service_)),
        resolver_(boost::asio::ip::tcp::resolver(this->service_)),
        deadline_(this->service_) {
    deadline_.expires_at(boost::posix_time::pos_infin);
    check_deadline();
}

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

void TcpClient::connect(const char *host, const char *port) {
    this->host_ = std::string(host);
    this->port_ = boost::lexical_cast<unsigned short>(port);

    boost::asio::connect(this->socket_, resolver_.resolve({host, port}));
}

void TcpClient::write(const std::string &message) {
    std::string data = message + "\r\n";

    deadline_.expires_from_now(boost::posix_time::seconds(TIMEOUT));

    boost::system::error_code ec = boost::asio::error::would_block;

    boost::asio::async_write(socket_, boost::asio::buffer(data), boost::lambda::var(ec) = boost::lambda::_1);

    do {
        service_.run_one();
    } while (ec == boost::asio::error::would_block);

    if (ec)
        throw boost::system::system_error(ec);
}

std::string TcpClient::read() {
    deadline_.expires_from_now(boost::posix_time::seconds(TIMEOUT));

    boost::system::error_code ec = boost::asio::error::would_block;

    boost::asio::async_read_until(socket_, input_buffer_, READ_UNTIL_DELIM,
                                  boost::lambda::var(ec) = boost::lambda::_1);

    do {
        service_.run_one();
    } while (ec == boost::asio::error::would_block);

    if (ec == boost::asio::error::eof) {
        std::cout << "Connection closed by server\n";
    }

    std::string received_data_str = this->to_string(input_buffer_);
    input_buffer_.consume(input_buffer_.size());  // Очистка буффера
    return received_data_str;
}

void TcpClient::check_deadline() {
    if (deadline_.expires_at() <= boost::asio::deadline_timer::traits_type::now()) {
        boost::system::error_code ignored_ec;
        socket_.close(ignored_ec);
        deadline_.expires_at(boost::posix_time::pos_infin);
    }

    deadline_.async_wait(boost::lambda::bind(&TcpClient::check_deadline, this));
}
