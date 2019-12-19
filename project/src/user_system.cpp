#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "user_system.h"
#include "json.h"

UserSystem::UserSystem() {}

std::string UserSystem::login(const std::string &login, const std::string &pass) const {
    bool status;
    std::string session = db_worker_.login(login, pass, status);
    boost::property_tree::ptree root;
    if (status) {
        root.put("status", "200");
        root.put("message", "User is logged in");
        root.put("session", session);
    } else {
        root.put("status", "401");
        root.put("message", "Invalid login or password");
    }

    return stringify_json(root);
}

std::string UserSystem::signup(const std::string &login, const std::string &pass) const {
    bool status;
    std::string session = db_worker_.signup(login, pass, status);
    boost::property_tree::ptree root;
    if (status) {
        root.put("status", "200");
        root.put("message", "User is registered");
        root.put("session", session);
    } else {
        root.put("status", "401");
        root.put("message", "Login is busy");
    }

    return stringify_json(root);
}

std::string UserSystem::increment_listening(int song_id, int user_id) const {
    boost::property_tree::ptree root;
    if (!db_worker_.is_song_exists(song_id)) {
        root.put("status", "400");
        root.put("message", "Error! Song does not exist");
        return stringify_json(root);
    }
    if (!db_worker_.is_user_exists(user_id)) {
        root.put("status", "400");
        root.put("message", "Error! User does not exist");
        return stringify_json(root);
    }

    int quantity_of_listening = db_worker_.increment_listening(song_id, user_id);
    root.put("status", "200");
    root.put("quantity_of_listening", quantity_of_listening);
    return stringify_json(root);
}

std::string UserSystem::like_song(int song_id, int user_id, bool value) const {
    boost::property_tree::ptree root;
    if (!db_worker_.is_song_exists(song_id)) {
        root.put("status", "400");
        root.put("message", "Error! Song does not exist");
        return stringify_json(root);
    }
    if (!db_worker_.is_user_exists(user_id)) {
        root.put("status", "400");
        root.put("message", "Error! User does not exist");
        return stringify_json(root);
    }

    db_worker_.like_song(song_id, user_id, value);
    root.put("status", "200");
    if (value) {
        root.put("message", "like delivered");
    } else {
        root.put("message", "dislike delivered");
    }

    return stringify_json(root);
}

int UserSystem::get_user_id(const std::string & session, bool &status) const {
    return db_worker_.get_user_id(session, status);
}

std::string UserSystem::logout(const std::string &session) const {
    db_worker_.logout(session);
    return on_fail(303, "Redirect to login page");
}

std::string UserSystem::get_login(const std::string &session) const {
    bool status;
    std::string login = db_worker_.get_login(session, status);
    boost::property_tree::ptree root;
    if (status) {
        root.put("status", "200");
        root.put("login", login);
    } else {
        root.put("status", "403");
        root.put("message", "Redirect to login page");
    }

    return stringify_json(root);
}
