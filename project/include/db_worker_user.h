#ifndef K_ON_DB_WORKER_USER_H
#define K_ON_DB_WORKER_USER_H

#include <string>
#include <map>

#include "db_wrapper.h"

class DbWorkerUser {
public:
    DbWorkerUser();
    ~DbWorkerUser();
    std::string login(const std::string &login, const std::string &pass, bool &status) const;
    std::string signup(const std::string &login, const std::string &pass, bool &status) const;
    int increment_listening(int song_id, int user_id) const;
    bool like_song(int song_id, int user_id, bool value) const;
    bool is_user_exists(int user_id) const;
    bool is_song_exists(int song_id) const;
    int get_user_id(const std::string &session, bool &status) const;
    void logout(const std::string &session) const;
    std::string get_login(const std::string session, bool &status) const;

private:
    DbWrapper db_wrapper_;
};


#endif  // K_ON_DB_WORKER_USER_H
