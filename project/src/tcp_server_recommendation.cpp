//
// Created by andrey on 23.11.2019.
//

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "tcp_server_recommendation.h"
#include "json.h"

TcpServerRecommendation::TcpServerRecommendation(unsigned short port) : TcpServer(port) {}

std::string TcpServerRecommendation::handle_request(const std::string &request) const {
    return on_fail(200, "Answer from recommendation server");git
}

