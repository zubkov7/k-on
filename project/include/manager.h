//
// Created by andrey on 22.11.2019.
//

#ifndef K_ON_MANAGER_H
#define K_ON_MANAGER_H

#include <string>
#include <vector>

#include "user.h"

class Manager(TcpClient) {
public:
    Manager();
    ~Manager();
    std::string handle_request(const std::string &request);
private:
    std::string on_user(const std::string &request);
    std::string on_recommendation(const std::string &request);
    user on_get_user(const int id);
    bool on_login(const std::string &login, const std::string &pass);
    bool on_register(const std::string &login, const std::string &pass);
    int on_inc_listening(const int song_id, const int user_id);
    bool on_like_song(const int song_id, const int user_id, const bool value);
    std::vector<Recommendations> on_get_recommendations(const int user_id);
    std::vector<Song> on_get_popular_songs(const int count);
    std::vector<Recommendations> on_update_recommendations(const int user_id);
};


#endif //K_ON_MANAGER_H
