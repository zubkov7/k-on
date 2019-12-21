#include <iostream>

#include "web_server.h"

int main(int argc, char *argv[]) {
    std::cout << "main thread is " << pthread_self() << std::endl;

    Web_server server;
    server.start();

    return 0;
}