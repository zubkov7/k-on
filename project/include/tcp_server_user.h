//
// Created by andrey on 23.11.2019.
//

#ifndef K_ON_TCP_SERVER_USER_H
#define K_ON_TCP_SERVER_USER_H

#include "user.h"

class TcpServerUser(TcpServer) {
public:
    TcpServerUser();
    ~TcpServerUser();
    void handle_request(const std::string request);

private:
    User user_;
    user on_get_user(const int id);
    bool on_login(const std::string &login, const std::string &pass);
    bool on_register(const std::string &login, const std::string &pass);
    int on_inc_listening(const int song_id, const int user_id);
    bool on_like_song(const int song_id, const int user_id, const bool value);
};


#endif //K_ON_TCP_SERVER_USER_H
