#ifndef K_ON_USER_H
#define K_ON_USER_H

#include <string>

#include "db_worker_user.h"
#include "db_entities.h"

class User {
public:
    User(const std::string &db_path, const std::string &host,
         const std::string &login, const std::string &pass);
    ~User() {}
    user get_user(const int id);
    bool login(const std::string &login, const std::string &pass);
    bool register_user(const std::string &login, const std::string &pass);
    int increment_listening(const int song_id, const int user_id);
    bool like_song(const int song_id, const int user_id, const bool value);

private:
    DBWorkerUser _db_worker;
    user _user;
};


#endif //K_ON_USER_H
