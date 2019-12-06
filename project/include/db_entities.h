#ifndef K_ON_DB_ENTITIES_H
#define K_ON_DB_ENTITIES_H

#include <iostream>


struct User {
    User(int id, const std::string &login, const std::string &password) : id(id), login(login),
                                                                          password(password) {}

    bool operator==(const User &user) const;

    int id;
    std::string login;
    std::string password;
};

struct Song {
    Song(int id, const std::string &name, const std::string &author, const std::string &genre, unsigned int duration,
         const std::string &date) : id(id), name(name), author(author), genre(genre),
                                    duration(duration), date(date) {}

    bool operator==(const Song &song) const;

    int id;
    std::string name;
    std::string author;
    std::string genre;
    unsigned int duration;
    std::string date;
};

struct LikeDislike {
    LikeDislike(int id, int user_id, int song_id, bool value) : id(id), user_id(user_id), song_id(song_id),
                                                                value(value) {}

    bool operator==(const LikeDislike &like_dislike) const;

    int id;
    int user_id;
    int song_id;
    bool value;
};

struct Listen {
    Listen(int id, int user_id, int song_id, unsigned int count) : id(id), user_id(user_id), song_id(song_id),
                                                                   count(count) {}

    bool operator==(const Listen &listen) const;

    int id;
    int user_id;
    int song_id;
    unsigned int count;
};

#endif  // K_ON_DB_ENTITIES__
