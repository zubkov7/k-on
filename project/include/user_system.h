#ifndef K_ON_USER_SYSTEM_H
#define K_ON_USER_SYSTEM_H

#include <string>

#include "db_worker_user.h"

class UserSystem {
public:
    UserSystem();

    std::string login(const std::string &login, const std::string &pass) const;
    std::string signup(const std::string &login, const std::string &pass) const;
    std::string increment_listening(int song_id, int user_id) const;
    std::string like_song(int song_id, int user_id, bool value) const;
    std::string logout(const std::string &session) const;
    std::string get_login(const std::string &session) const;
    int get_user_id(const std::string &session, bool &status) const;

private:
    DbWorkerUser db_worker_;
};


#endif  // K_ON_USER_SYSTEM_H
