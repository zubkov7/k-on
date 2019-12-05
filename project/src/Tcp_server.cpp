//
// Created by andrey on 04.12.2019.
//

#include <thread>

#include "Tcp_server.h"

std::string Tcp_server::handle_request(const std::string &request) {
    return request;
}

Tcp_server::Tcp_server(unsigned short port) :
    acceptor_(service_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    port_(port) {}

std::string Tcp_server::to_string(boost::asio::streambuf &buf) {
    std::ostringstream tmp;
    tmp << &buf;
    return tmp.str();
}

void Tcp_server::start_server() {
    std::cout << "Start server on: " << this->acceptor_.local_endpoint().address() << std::endl;
    std::cout << "Listen on port: " << this->port_ << std::endl;

    while (true) {
        boost::asio::ip::tcp::socket sock(this->service_);
        this->acceptor_.accept(sock);
        std::thread(&Tcp_server::on_accept, this, std::move(sock)).detach();
    }
}

void Tcp_server::on_accept(boost::asio::ip::tcp::socket sock) {
    std::cout << "+client from: "
              << sock.remote_endpoint().address().to_string()
              << ':'
              << sock.remote_endpoint().port()
              << std::endl;

    try {
        // Чтение данных из сокета клиента
        boost::asio::streambuf received_data;
        boost::asio::read_until(sock, received_data, READ_UNTIL_DELIM);

        std::string received_data_str = this->to_string(received_data);
        std::cout << "Received data: " << received_data_str;

        // Запись ответа клиенту
        boost::asio::streambuf answer;
        std::ostream out(&answer);
        out << this->handle_request(received_data_str) << std::endl;
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
