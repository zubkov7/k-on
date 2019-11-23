//
// Created by andrey on 23.11.2019.
//

#ifndef K_ON_TCP_SERVER_USER_H
#define K_ON_TCP_SERVER_USER_H

#include <string>

#include "user.h"
#include "db_entities.h"

class TcpServerUser(TcpServer) {
public:
    TcpServerUser(const std::string &db_path, const std::string &host,
                  const std::string &login, const std::string &pass);
    ~TcpServerUser();
    void handle_request(const std::string request);

private:
    User _user;

private:
    user on_get_user(const int id);
    bool on_login(const std::string &login, const std::string &pass);
    bool on_register(const std::string &login, const std::string &pass);
    int on_inc_listening(const int song_id, const int user_id);
    bool on_like_song(const int song_id, const int user_id, const bool value);
};


#endif //K_ON_TCP_SERVER_USER_H
