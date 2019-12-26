//
// Created by andrey on 23.11.2019.
//

#ifndef K_ON_TCP_SERVER_USER_H
#define K_ON_TCP_SERVER_USER_H

#include <string>
#include <boost/property_tree/ptree.hpp>

#include "user_system.h"
#include "tcp_server.h"

class TcpServerUser : public TcpServer {
public:
    TcpServerUser(unsigned short port);
private:
    UserSystem user_system_;
    
private:
    std::string handle_request(const std::string &request) const override;
    std::string on_login(const boost::property_tree::ptree &root) const;
    std::string on_signup(const boost::property_tree::ptree &root) const;
    std::string on_inc_listening(const boost::property_tree::ptree &root) const;
    std::string on_like_song(const boost::property_tree::ptree &root) const;
    std::string on_get_user_id(const boost::property_tree::ptree &root) const;
    std::string on_logout(const boost::property_tree::ptree &root) const;
    std::string on_get_user_login(const boost::property_tree::ptree &root) const;
};


#endif  // K_ON_TCP_SERVER_USER_H
