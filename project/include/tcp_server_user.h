//
// Created by andrey on 23.11.2019.
//

#ifndef K_ON_TCP_SERVER_USER_H
#define K_ON_TCP_SERVER_USER_H

#include <string>

#include "user_system.h"
#include "tcp_server.h"

class TcpServerUser : public TcpServer {
public:
    TcpServerUser(unsigned short port);
private:
    UserSystem user_system_;
    
private:
    std::string handle_request(const std::string &request) const override;
    std::string on_login(const std::string &login, const std::string &pass) const;
    std::string on_signup(const std::string &login, const std::string &pass) const;
    std::string on_inc_listening(int song_id, int user_id) const;
    std::string on_like_song(int song_id, int user_id, bool value) const;
    std::string on_fail(int code, const std::string &message) const;
};


#endif  // K_ON_TCP_SERVER_USER_H
