#include <thread>
#include <iostream>
#include <boost/beast/http/parser.hpp>
#include <boost/beast/http.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "server.h"

int main(int argc, char *argv[]) {

    std::cout << "main thread is " << pthread_self() << std::endl;

    Web_server serv;
    serv.start();
    return 0;
}