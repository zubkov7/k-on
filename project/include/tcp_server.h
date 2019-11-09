#ifndef PROJECT_INCLUDE_TCP_SERVER_H_
#define PROJECT_INCLUDE_TCP_SERVER_H_

#include "recommendation_system.h"

class TcpServer {
public:
    TcpServer();
    ~TcpServer();

    void start();           // устанавливает соединение с мастером
private:
    RecommendationSystem recommendations;

    void process_request(); // обрабатывает запрос
};

#endif  // PROJECT_INCLUDE_TCP_SERVER_H_
