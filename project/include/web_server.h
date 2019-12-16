#ifndef K_ON_WEB_SERVER_H
#define K_ON_WEB_SERVER_H


#include "boost/asio.hpp"
#include "client.h"
#include <string>

class Web_server {
public:
    Web_server() : acceptor_(service_),config_path("") {}
    Web_server(std::string conf) : acceptor_(service_),config_path(conf){}
    ~Web_server() {}
    void start();
    void restart();
    void stop();

private:
    int port;
    boost::asio::ip::address host;
    int threads_num;
    std::string html_path;
    std::string config_path;
    boost::asio::io_service service_;
    boost::asio::ip::tcp::acceptor acceptor_;

private:
    std::map<std::string, std::string> read_config();
    void on_accept(std::shared_ptr<Client> c, const boost::system::error_code &e);
    void start_accept();
    void run();
};


#endif //K_ON_WEB_SERVER_H