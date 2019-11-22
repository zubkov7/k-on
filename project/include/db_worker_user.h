#ifndef K_ON_DB_WORKER_USER_H
#define K_ON_DB_WORKER_USER_H

#include <string>
#include <map>

struct user {
    int id;
    std::string login;
    std::string pass;

    user(const int id, const std::string &login, const std::string &pass) : id(id), login(login), pass(pass) {}
};

class DbWorkerUser {
public:
    DbWorkerUser(const std::string &user, const std::string &pass);
    ~DbWorkerUser() {}
    user get_user(const int id);
    bool login(const std::string &login, const std::string &pass);
    bool register_user(const std::string &login, const std::string &pass);
    int increment_listening(const int song_id, const int user_id);
    bool like_song(const int song_id, const int user_id, const bool value);

private:
    DbWrapper db_wrapper;
    bool is_login_available(const std::string &login);
};


#endif //K_ON_DB_WORKER_USER_H
