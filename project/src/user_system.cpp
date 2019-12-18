#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "user_system.h"

UserSystem::UserSystem() {}

std::string UserSystem::login(const std::string &login, const std::string &pass) const {
    bool status = db_worker_.login(login, pass);
    boost::property_tree::ptree root;
    if (status) {
        root.put("status", "200");
        root.put("message", "User is logged in");
    } else {
        root.put("status", "401");
        root.put("message", "Invalid login or password");
    }
    std::stringstream answer;
    boost::property_tree::write_json(answer, root);
    return answer.str();
}

std::string UserSystem::signup(const std::string &login, const std::string &pass) const {
    bool status = db_worker_.signup(login, pass);
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
