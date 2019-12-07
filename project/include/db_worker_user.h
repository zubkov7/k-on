#ifndef K_ON_DB_WORKER_USER_H
#define K_ON_DB_WORKER_USER_H

#include <string>
#include <map>

#include "db_entities.h"
#include "db_wrapper.h"

class DbWorkerUser {
public:
    DbWorkerUser();
    ~DbWorkerUser();
    user get_user(int id);
    bool login(const std::string &login, const std::string &pass);
    bool register_user(const std::string &login, const std::string &pass);
    int increment_listening(int song_id, int user_id);
    bool like_song(int song_id, int user_id, bool value);
    int get_listening(int song_id, int user_id);
    bool get_like_song(int song_id, int user_id);

private:
    DbWrapper db_wrapper_;

private:
    bool is_login_available(const std::string &login);
};


#endif  // K_ON_DB_WORKER_USER_H
