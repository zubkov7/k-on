#ifndef K_ON_DB_ENTITIES_H
#define K_ON_DB_ENTITIES_H

struct user {
    int id;
    std::string login;
    std::string pass;

    user(const int id, const std::string &login, const std::string &pass) : id(id), login(login), pass(pass) {}

    bool operator==(const user &a) const;
};



#endif //K_ON_DB_ENTITIES_H
