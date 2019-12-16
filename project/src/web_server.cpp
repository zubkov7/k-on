#include "web_server.h"
#include <boost/beast/http/parser.hpp>
#include <boost/beast/http.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <functional>
#include <iostream>
#include <fstream>

#define DEFAULT_PORT 5555
#define DEFAULT_NUM_THREADS 4
#define DEFAULT_CONFIG_PATH "/Users/elenaelizarova/CLionProjects/k-on/project/config.txt"

void Web_server::start() {
    if (config_path =="")
    {
        config_path=DEFAULT_CONFIG_PATH;
    }
    std::map<std::string, std::string> m = read_config();
    port = atoi(m["PORT"].c_str());
    if (port > 65535 || port < 1024)
        port = DEFAULT_PORT;
    threads_num = atoi(m["NUM_THREADS"].c_str());
    if (threads_num > 10)
        threads_num = DEFAULT_NUM_THREADS;

    host = boost::asio::ip::make_address(m["HOST"].c_str());
    //host = boost::asio::ip::address::from_string("0.0.0.0");

    boost::asio::ip::tcp::endpoint endpoint(host, port);
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen(1024);
    start_accept();
    std::cerr << "listen on port: " << port << std::endl;


    std::vector<std::thread> threads;
    for (int i = 0; i < threads_num; ++i)
        threads.emplace_back(std::bind(&Web_server::run, this));
    for (auto &thread : threads)
        thread.join();
}

void Web_server::on_accept(std::shared_ptr<Client> c, const boost::system::error_code &e) {
    if (e)
        return;
    std::cerr << "+client: " << c->sock().remote_endpoint().address().to_string().c_str() << std::endl;
    c->read();
    start_accept();
}

void Web_server::start_accept() {
    std::shared_ptr<Client> c(new Client(service_));
    acceptor_.async_accept(c->sock(),
                           boost::bind(&Web_server::on_accept, this, c,
                                       boost::asio::placeholders::error));
}

void Web_server::run() {
    service_.run();
}

std::map<std::string, std::string> Web_server::read_config() {

    std::string line;
    std::map<std::string, std::string> m;

    std::ifstream in(config_path); // окрываем файл для чтения
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