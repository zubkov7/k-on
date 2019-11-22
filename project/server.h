#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <thread>
#include <vector>
#include <string>


//#include <boost/asio/ip/tcp.hpp>    //socket
//#include <boost/beast/http.hpp>     //Request
#include "HTML.h"                   //HTML
//#include "include/manager.h"      //Manager

//#include <boost/asio.hpp>
//#include <boost/asio/steady_timer.hpp>

class HTTP_worker {
public:
    bool start_work();

    socket set_socket();

    bool is_busy(busy);

    HTTP_worker() {};

    ~HTTP_worker() {};

private:
    //разноситьь по приватам функции и поля
    int timeout;

    Request request;

    socket client_socket;

    bool busy;

    HTML html;

    Manager manager;

private:

    void handle();

    bool write(client_socket);

    bool read(client_socket);

    bool process_request(request);

    bool check_deadline(timeout);
}

class HTTP_master {
	
public:
    ~HTTP_master() {};
private:
    HTTP_master(server, port, workers) {};
	
    vector <HTTP_worker> workers;
	
    socket server_socket;
    std::string server;
	
    int port;
	
    int time_sleep;
	
private:
    HTTP_worker create_worker(workers);

    bool kill_worker(HTTP_worker);

    bool connect(client_socket, workers);

    bool read_socket(server_socket);

    bool get_free_worker(workers);


}

class Web_server {
public:
    Web_server() {};

    ~Web_server() {};

    bool start();

    bool restart();

    bool stop();

private:
    std::string user;
	
    int pid;
private:
    bool read_config();

    bool kill_master(HTTP_master);

    HTTP_master master;

    HTTP_master create_master(master);

}

#endif
