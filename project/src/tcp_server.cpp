//
// Created by andrey on 04.12.2019.
//

#include <thread>

#include "tcp_server.h"

std::string TcpServer::handle_request(const std::string &request) const {
    return request;
}

TcpServer::TcpServer(unsigned short port) :
    acceptor_(service_),
    port_(port) {}

std::string TcpServer::to_string(boost::asio::streambuf &buf) const {
    std::ostringstream tmp;
    tmp << &buf;
    std::string str = tmp.str();
    str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    return str;
}

void TcpServer::start_server() {
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address(HOST), port_);
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen(MAX_PENDING_CONNECTIONS);
    std::cout << "Start server on: " << this->acceptor_.local_endpoint().address() << std::endl;
    std::cout << "Listen on port: " << this->port_ << std::endl;

    while (true) {
        boost::asio::ip::tcp::socket sock(this->service_);
        this->acceptor_.accept(sock);
        on_accept(std::move(sock));
    }
}

void TcpServer::on_accept(boost::asio::ip::tcp::socket sock) const {
    std::cout << "+client from: "
              << sock.remote_endpoint().address().to_string()
              << ':'
              << sock.remote_endpoint().port()
              << std::endl;

    try {
        // Чтение данных из сокета клиента
        boost::asio::streambuf received_data;
        boost::asio::read_until(sock, received_data, READ_UNTIL_DELIM);

        std::string received_data_str = to_string(received_data);
        std::cout << "Received data: " << received_data_str << std::endl;

        // Запись ответа клиенту
        boost::asio::streambuf answer;
        std::ostream out(&answer);

        out << handle_request(received_data_str) << std::endl;
        boost::asio::write(sock, answer);

        // Закрытие соединения с клиентом
        std::cout << "-client: Connection closed by server\n";
        sock.close();
    }
    catch (boost::system::system_error const &e) {
        if (e.code() == boost::asio::error::eof) {  // Клиент закрыл соединение
            std::cout << "-client: Connection closed by peer\n";
            sock.close();
        } else {
            boost::throw_exception(e);
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}
