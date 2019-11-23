#ifndef K_ON_DB_ENTITIES_H
#define K_ON_DB_ENTITIES_H

#include <iostream>

struct User {
    User(int id, std::string login, std::string password) : id(id), login(std::move(login)),
                                                            password(std::move(password)) {}

    int id;
    std::string login;
    std::string password;
};

struct Song {
    Song(int id, std::string name, std::string author, std::string genre, int duration) : id(id), name(
            std::move(name)), author(std::move(author)), genre(
            std::move(genre)), duration(duration) {}

    int id;
    std::string name;
    std::string author;
    std::string genre;
    int duration;
};

struct LikeDislike {
    LikeDislike(int id, int user_id, int song_id, bool value) : id(id), user_id(user_id), song_id(song_id),
                                                                value(value) {}

    int id;
    int user_id;
    int song_id;
    bool value;
};

struct Listen {
    Listen(int id, int user_id, int song_id, int count) : id(id), user_id(user_id), song_id(song_id), count(count) {}

    int id;
    int user_id;
    int song_id;
    int count;
};

struct Recommendation {
    Recommendation(int id, int user_id, int song_id) : id(id), user_id(user_id), song_id(song_id) {}

    int id;
    int user_id;
    int song_id;
};

#endif //K_ON_DB_ENTITIES__
