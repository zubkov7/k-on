#include <sstream>

#include "user_system.h"

UserSystem::UserSystem() {}

std::string UserSystem::login(const std::string &login, const std::string &pass) const {
    bool status = db_worker_.login(login, pass);
    if (status) {
        return "User is logged in";
    } else {
        return "Invalid login or password";
    }
}

std::string UserSystem::register_user(const std::string &login, const std::string &pass) const {
    bool status = db_worker_.sign_up(login, pass);
    if (status) {
        return "User is registered";
    } else {
        return "Login is busy";
    }
}

std::string UserSystem::increment_listening(int song_id, int user_id) const {
    if (!db_worker_.is_song_exists(song_id)) {
        return "Error! Song does not exist";
    }
    if (!db_worker_.is_user_exists(user_id)) {
        return "Error! User does not exist";
    }

    int quantity_of_listening = db_worker_.increment_listening(song_id, user_id);
    std::stringstream answer;
    answer << "Quantity of listening now is "
           << quantity_of_listening;
    return answer.str();
}

std::string UserSystem::like_song(int song_id, int user_id, bool value) const {
    if (!db_worker_.is_song_exists(song_id)) {
        return "Error! Song does not exist";
    }
    if (!db_worker_.is_user_exists(user_id)) {
        return "Error! User does not exist";
    }

    db_worker_.like_song(song_id, user_id, value);
    if (value) {
        return "Like delivered";
    } else {
        return "Dislike delivered";
    }
}
