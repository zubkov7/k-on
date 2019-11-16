#ifndef PROJECT_INCLUDE_TCP_SERVER_H_
#define PROJECT_INCLUDE_TCP_SERVER_H_

#include "recommendation_system.h"

class TcpServer {
public:
    TcpServer();
    ~TcpServer();

    void start();
    void create_socket(int port);

private:
    RecommendationSystem recommendation_system;

    void process_request();
};

#endif  // PROJECT_INCLUDE_TCP_SERVER_H_
