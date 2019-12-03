#ifndef SERVER_H
#define SERVER_H

#include <thread>
#include <vector>
#include <string>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/http.hpp>



//#include <boost/asio/ip/tcp.hpp>    
//#include <boost/beast/http.hpp>     
#include "HTML.h"
//#include "include/manager.h"

class HTTP_worker {
public:
    HTTP_worker() {}

    ~HTTP_worker() {}

    bool start_work();

    boost::asio::ip::tcp::socket set_socket();

    bool is_busy(bool busy);

private:
    //разноситьь по приватам функции и поля
    int timeout;

//    Request request;

//    socket client_socket;

    bool busy;

    HTML html;

//    Manager manager;

private:

    void handle();

//    bool write(socket client_socket);

//    bool read(socket client_socket);

//    bool process_request(Request request);

    bool check_deadline(int timeout);
};

class HTTP_master {
public:
    ~HTTP_master() {}

private:
    HTTP_master(std::string server, int port, int nuw_workers) {}

    std::vector<HTTP_worker> workers;
//    socket server_socket;
    std::string server;
    int port;
    int time_sleep;

    HTTP_worker create_worker(std::vector<HTTP_worker> workers);

    bool kill_worker(HTTP_worker worker);

//    bool connect(socket client_socket, std::vector<HTTP_worker> workers);

//    bool read_socket(socket server_socket);

    bool get_free_worker(std::vector<HTTP_worker> workers);


};

class Web_server {
public:
    Web_server() {}

    ~Web_server() {}

    bool start();

    bool restart();

    bool stop();

private:
    std::string user;
    int pid;

    bool read_config();

    bool kill_master(HTTP_master master);

//    HTTP_master master = HTTP_master::HTTP_master("", 0, 0)

 //   HTTP_master create_master(HTTP_master master);

};

#endif
