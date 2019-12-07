#include "server.h"
#include <boost/beast/http/parser.hpp>
#include <boost/beast/http.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <functional>
#include <iostream>
#include <fstream>

#define DEFAULT_PORT 5555
#define DEFAULT_NUM_THREADS 4

#define BOOST_ASIO_HAS_STD_STRING_VIEW

void Client::read() {
    try {
        m_Sock.async_read_some(
                boost::asio::buffer(m_Buf),
                boost::bind(&Client::handleRead, shared_from_this(),
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

void Client::handleRead(const boost::system::error_code &e,
                        std::size_t bytes_transferred) {
    if (e == boost::asio::error::eof) {
        std::cerr << "-client: " << m_Sock.remote_endpoint().address().to_string()
                  << std::endl;
    }
    if (e)
        return;

    std::cerr << "read: " << bytes_transferred << " bytes" << std::endl;
    std::cerr << "read thread is " << pthread_self() << std::endl;


    boost::beast::http::request_parser<boost::beast::http::string_body> p;
    boost::beast::error_code er;
    p.put(boost::asio::buffer(m_Buf), er);
    std::cerr << p.release() << std::endl;
    memset(m_Buf,'\0',1024);

    /*Tcp_client tcp_client;
    tcp_client.connect("0.0.0.0", "8080");
    tcp_client.write(p.release().target());
    std::string answer_from_user_server = tcp_client.read();
    tcp_client.close_connection();*/

    int k = snprintf(m_SendBuf, sizeof(m_SendBuf), "HTTP/1.1 200 OK\r\n");
    k += snprintf(m_SendBuf + k, sizeof(m_SendBuf) - k,
                  "Content-Length: 500\r\n\r\n");

    const char *html = "<!DOCTYPE html>\n"
                       "<html lang=\"en\">\n"
                       "<head>\n"
                       "    <meta charset=\"UTF-8\">\n"
                       "    <title>Title</title>\n"
                       "</head>\n"
                       "<body>\n"
                       "<h3>Hello world</h3>"
                       "</body>\n"
                       "</html>";

    k += snprintf(m_SendBuf + k, sizeof(m_SendBuf) - k,
                  "%s", html);

    m_Sock.async_write_some(
            boost::asio::buffer(m_SendBuf),
            [self = shared_from_this()](const boost::system::error_code &e,
                                        std::size_t bytes_transferred) -> void {
                // После того, как запишем ответ, можно снова читать
                self->read();
            });
}

void Web_server::start() {
    std::map<std::string, std::string> m;
    m = read_config();


    port = atoi(m["PORT"].c_str());
    if (port > 65535 || port < 1024)
        port = DEFAULT_PORT;
    threads_num = atoi(m["NUM_THREADS"].c_str());
    if (threads_num > 10)
        threads_num = DEFAULT_NUM_THREADS;

    host = boost::asio::ip::make_address(m["HOST"].c_str());

    boost::asio::ip::tcp::endpoint endpoint(host, port);
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen(1024);
    startAccept();
    std::cerr << "listen on port: " << port << std::endl;


    std::vector<std::thread> threads;
    for (int i = 0; i < threads_num; ++i)
        threads.emplace_back(std::bind(&Web_server::run, this));
    for (auto &thread : threads)
        thread.join();
    //      run();
}

void Web_server::onAccept(std::shared_ptr<Client> c, const boost::system::error_code &e) {
    if (e)
        return;
    std::cerr << "+client: " << c->sock().remote_endpoint().address().to_string().c_str() << std::endl;
    c->read();
    startAccept();
}

void Web_server::startAccept() {
    std::shared_ptr<Client> c(new Client(service_));
    acceptor_.async_accept(c->sock(),
                           boost::bind(&Web_server::onAccept, this, c,
                                       boost::asio::placeholders::error));
}

void Web_server::run() {
    service_.run();
}

std::map<std::string, std::string> Web_server::read_config() {

    std::string line;
    std::map<std::string, std::string> m;

    std::ifstream in("/Users/elenaelizarova/CLionProjects/k-on/project/config.txt"); // окрываем файл для чтения
    if (in.is_open()) {
        while (getline(in, line)) {
            std::string key, val;
            std::istringstream iss(line);

            while (std::getline(std::getline(iss, key, ':') >> std::ws, val)) { m[key] = val; }
        }
    }
    in.close();
    return m;
}
