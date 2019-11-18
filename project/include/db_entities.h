#ifndef K_ON_DB_ENTITIES_H
#define K_ON_DB_ENTITIES_H

#include <iostream>

struct User {
    int id;
    std::string login;
    std::string password;
};

struct Song {
    int id;
    std::string name;
    std::string author;
    std::string genre;
    int duration;
};

struct LikeDislike {
    int id;
    int user_id;
    int song_id;
    bool value;
};

struct Listen {
    int id;
    int user_id;
    int song_id;
    int count;
};

struct Recommendation {
    int id;
    int user_id;
    int song_id;
};

#endif //K_ON_DB_ENTITIES__
