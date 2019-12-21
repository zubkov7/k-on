#include "tcp_server_recommendation.h"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        std::cout << "Please, use user_server port_number\n";
        return 1;
    }

    int port = atoi(argv[1]);
    if (port < 1024 || port > 65535) {
        std::cout << "Port number must be a number from 1024 to 65535!\n";
        return 1;
    }

    try {
        TcpServerRecommendation server(port);
        server.start_server();
    }
    catch (boost::system::system_error const &e) {
        std::cout << e.what() << std::endl;
        if (e.code() == boost::asio::error::address_in_use) {
            std::cout << "Address already in use\n";
        } else {
            boost::throw_exception(e);
        }
    }
}