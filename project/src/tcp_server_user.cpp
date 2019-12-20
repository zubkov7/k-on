//
// Created by andrey on 23.11.2019.
//

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "tcp_server_user.h"
#include "json.h"

TcpServerUser::TcpServerUser(unsigned short port) : TcpServer(port) {}

std::string TcpServerUser::handle_request(const std::string &request) const {
    try {
        boost::property_tree::ptree root = parse_to_json(request);
        std::string method = root.get<std::string>("method");

        if (method == "login") {
            return on_login(root);
        }
        if (method == "signup") {
            return on_signup(root);
        }
        if (method == "listen") {
            return on_inc_listening(root);
        }
        if (method == "like") {
            return on_like_song(root);
        }
        if (method == "logout") {
            return on_logout(root);
        }
        if (method == "get_user_id") {
            return on_get_user_id(root);
        }

        return on_fail(500, "Internal server error: request to the wrong method");
    }
    catch (boost::property_tree::ptree_bad_path const &e) {
        std::cout << e.what() << std::endl;
        return on_fail(500, "Internal server error");
    }
    catch (boost::property_tree::json_parser_error const &e) {
        std::cout << e.what() << std::endl;
        return on_fail(500, "Internal server error");
    }
}

std::string TcpServerUser::on_login(const boost::property_tree::ptree &root) const {
    std::string login = root.get<std::string>("login");
    std::string password = root.get<std::string>("password");
    return user_system_.login(login, password);
}

std::string TcpServerUser::on_signup(const boost::property_tree::ptree &root) const {
    std::string login = root.get<std::string>("login");
    std::string password = root.get<std::string>("password");
    return user_system_.signup(login, password);
}

std::string TcpServerUser::on_inc_listening(const boost::property_tree::ptree &root) const {
    int song_id = root.get<int>("song_id");
    std::string session = root.get<std::string>("session");

    bool status;
    int user_id = user_system_.get_user_id(session, status);

    if (status) {
        return user_system_.increment_listening(song_id, user_id);
    } else {
        return on_fail(401, "Unauthorized");
    }
}

std::string TcpServerUser::on_like_song(const boost::property_tree::ptree &root) const {
    int song_id = root.get<int>("song_id");
    bool like_value = root.get<bool>("like");
    std::string session = root.get<std::string>("session");

    bool status;
    int user_id = user_system_.get_user_id(session, status);

    if (status) {
        return user_system_.like_song(song_id, user_id, like_value);
    } else {
        return on_fail(401, "Unauthorized");
    }
}

std::string TcpServerUser::on_logout(const boost::property_tree::ptree &root) const {
    std::string session = root.get<std::string>("session");
    return user_system_.logout(session);
}

std::string TcpServerUser::on_get_user_id(const boost::property_tree::ptree &root) const {
    std::string session = root.get<std::string>("session");

    bool status;
    int user_id = user_system_.get_user_id(session, status);

    if (status) {
        boost::property_tree::ptree answer;
        answer.put("login", user_system_.get_login(session));
        answer.put("status", "200");
        answer.put("user_id", user_id);
        return stringify_json(answer);
    } else {
        return on_fail(401, "Unauthorized");
    }
}
