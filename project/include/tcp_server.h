#ifndef K_ON_TCP_SERVER_H
#define K_ON_TCP_SERVER_H

#include "recommendation_system.h"

class TcpServer {
public:
    TcpServer();
    ~TcpServer();

    void start();
    void create_socket(int port);

private:
    RecommendationSystem _recommendation_system;

private:
    void process_request();
};

#endif  // K_ON_TCP_SERVER_H
