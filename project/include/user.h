#ifndef K_ON_USER_H
#define K_ON_USER_H

#include <string>

#include "db_worker_user.h"
#include "db_entities.h"

class User {
public:
    User();

    user get_user(int id);
    bool login(const std::string &login, const std::string &pass);
    bool register_user(const std::string &login, const std::string &pass);
    int increment_listening(int song_id, int user_id);
    bool like_song(int song_id, int user_id, bool value);

private:
    DbWorkerUser db_worker_;
    user user_;
};


#endif //K_ON_USER_H
