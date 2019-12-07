//
// Created by andrey on 23.11.2019.
//

#ifndef K_ON_TCP_SERVER_USER_H
#define K_ON_TCP_SERVER_USER_H

#include <string>

#include "user.h"
#include "tcp_server.h"

class TcpServerUser : public TcpServer {
public:
    TcpServerUser(unsigned short port);
private:
    User user_;
    
private:
    std::string handle_request(const std::string &request) override;
    std::string on_get_user(int id);
    std::string on_login(const std::string &login, const std::string &pass);
    std::string on_register(const std::string &login, const std::string &pass);
    std::string on_inc_listening(int song_id, int user_id);
    std::string on_like_song(int song_id, int user_id, bool value);
};


#endif  // K_ON_TCP_SERVER_USER_H
