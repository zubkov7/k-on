//
// Created by andrey on 23.11.2019.
//

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "tcp_server_user.h"

TcpServerUser::TcpServerUser(unsigned short port) : TcpServer(port) {}

std::string TcpServerUser::handle_request(const std::string &request) const {
    boost::property_tree::ptree root;
    std::stringstream request_stream(request);
    boost::property_tree::read_json(request_stream, root);

    std::string method;
    if (root.find("method") != root.not_found()) {
        method = root.get<std::string>("method");
    } else {
        return on_fail(500, "internal server error");
    }

    if (method == "login") {
        std::string login = root.get<std::string>("login");
        std::string password = root.get<std::string>("password");
        return on_login(login, password);
    }
    if (method == "signup") {
        return on_signup("admin", "password");
    }
    if (method == "listen") {
        return on_inc_listening(1, 1);
    }
    if (method == "like") {
        return on_like_song(1, 1, false);
    }
    if (method == "logout") {
        // TODO () : add logout implementation
        return "Answer on logout";
    }

    return "Wrong command!";
}

std::string TcpServerUser::on_login(const std::string &login, const std::string &pass) const {
    // TODO() : вызывается метод класса UserSystem.login() и генерируется ответ в виде строки
    return user_system_.login(login, pass);
}

std::string TcpServerUser::on_signup(const std::string &login, const std::string &pass) const {
    // TODO() : вызывается метод класса UserSystem.sign_up() и генерируется ответ в виде строки
    return user_system_.signup(login, pass);
}

std::string TcpServerUser::on_inc_listening(int song_id, int user_id) const {
    // TODO() : вызывается метод класса UserSystem.increment_listening() и генерируется ответ в виде строки
    return user_system_.increment_listening(song_id, user_id);
}

std::string TcpServerUser::on_like_song(int song_id, int user_id, bool value) const {
    // TODO() : вызывается метод класса UserSystem.like_song() и генерируется ответ в виде строки
    return user_system_.like_song(song_id, user_id, value);
}

std::string TcpServerUser::on_fail(int code, const std::string &message) const {
    boost::property_tree::ptree root;
    root.put("status", code);
    root.put("message", message);

    std::stringstream answer;
    boost::property_tree::write_json(answer, root);

    return answer.str();
}
