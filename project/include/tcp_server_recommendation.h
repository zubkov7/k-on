//
// Created by andrey on 21.12.2019.
//

#ifndef K_ON_TCP_SERVER_RECOMMENDATION_H
#define K_ON_TCP_SERVER_RECOMMENDATION_H

#include "tcp_server.h"

class TcpServerRecommendation : public TcpServer {
public:
    TcpServerRecommendation(unsigned short port);
private:

private:
    std::string handle_request(const std::string &request) const override;
};

#endif //K_ON_TCP_SERVER_RECOMMENDATION_H
