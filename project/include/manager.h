//
// Created by andrey on 22.11.2019.
//

#ifndef K_ON_MANAGER_H
#define K_ON_MANAGER_H

#include <string>
#include <boost/property_tree/ptree.hpp>

#include "tcp_client.h"
#include "url_parser.h"

#define USER_HOST "0.0.0.0"
#define USER_PORT "7777"
#define RECOMMENDATION_HOST "0.0.0.0"
#define RECOMMENDATION_PORT "8888"

class Manager : public TcpClient {
public:
    Manager() {}
    ~Manager() {}
    std::string handle_request(const std::string &request, const std::string &session);

private:
    std::string on_auth(const UrlParser &url_parser, const std::string &method);
    std::string on_logout(const std::string &session);
    std::string on_listen(const UrlParser &url_parser, const std::string &session);
    std::string on_like(const UrlParser &url_parser, const std::string &session);
    std::string on_index_or_update(const std::string &session, const std::string &method);
    std::string on_top(const std::string &session);
    std::string on_recent(const std::string &session);
    std::string on_similar_song(const UrlParser &url_parser, const std::string &session);
    void add_login(boost::property_tree::ptree &root, const std::string &session);
};


#endif  // K_ON_MANAGER_H
