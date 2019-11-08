#ifndef PROJECT_INCLUDE_TCP_SERVER_H_
#define PROJECT_INCLUDE_TCP_SERVER_H_

#include "recommendation_system.h"

class TCP_server {
public:
    TCP_Server() {};
    ~TCP_Server() {};

    void start();           // устанавливает соединение с мастером
private:
    void process_request(); // обрабатывает запрос
    RecommendationSystem recommendations;
};

#endif  // PROJECT_INCLUDE_TCP_SERVER_H_
