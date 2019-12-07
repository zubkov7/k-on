#include "tcp_server_user.h"

#define PORT 7777

int main(int argc, char *argv[]) {
    try {
        TcpServerUser server(PORT);
        server.start_server();
    }
    catch (boost::system::system_error const &e) {
        if (e.code() == boost::asio::error::address_in_use) {
            std::cout << "Address already in use\n";
        } else {
            boost::throw_exception(e);
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }

    return 0;
}