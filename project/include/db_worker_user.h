#ifndef K_ON_DB_WORKER_USER_H
#define K_ON_DB_WORKER_USER_H

#include <string>
#include <map>

#include "db_entities.h"

class DbWorkerUser {
public:
    DbWorkerUser(const std::string &db_path, const std::string &host,
                 const std::string &login, const std::string &pass);
    ~DbWorkerUser() {}
    user get_user(const int id);
    bool login(const std::string &login, const std::string &pass);
    bool register_user(const std::string &login, const std::string &pass);
    int increment_listening(const int song_id, const int user_id);
    bool like_song(const int song_id, const int user_id, const bool value);
    int get_listening(const int song_id, const int user_id);
    bool get_like_song(const int song_id, const int user_id);

private:
    DbWrapper _db_wrapper;

private:
    bool is_login_available(const std::string &login);
};


#endif //K_ON_DB_WORKER_USER_H
