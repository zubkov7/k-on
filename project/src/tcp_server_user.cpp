//
// Created by andrey on 23.11.2019.
//

#include "tcp_server_user.h"

TcpServerUser::TcpServerUser(unsigned short port) : TcpServer(port) {}

std::string TcpServerUser::handle_request(const std::string &request) {
    // TODO() : по запросу вызывает нужные методы (сервера) on_get_user...
    if (request == "get user") {
        return on_get_user(1);
    }
    if (request == "login") {
        return on_login("login", "password");
    }
    if (request == "register") {
        return on_register("login", "password");
    }
    if (request == "increment listening") {
        return on_inc_listening(1, 1);
    }
    if (request == "like song") {
        return on_like_song(1, 1, true);
    }

    return "Wrong command!";
}

std::string TcpServerUser::on_get_user(int id) {
    // TODO() : вызывается метод класса User.get_user() и генерируется ответ в виде строки
    user_.get_user(1);
    return "Answer on get user";
}

std::string TcpServerUser::on_login(const std::string &login, const std::string &pass) {
    // TODO() : вызывается метод класса User.login() и генерируется ответ в виде строки
    user_.login("login", "password");
    return "Answer on user login";
}

std::string TcpServerUser::on_register(const std::string &login, const std::string &pass) {
    // TODO() : вызывается метод класса User.register_user() и генерируется ответ в виде строки
    user_.register_user("login", "password");
    return "Answer on user register";
}

std::string TcpServerUser::on_inc_listening(int song_id, int user_id) {
    // TODO() : вызывается метод класса User.increment_listening() и генерируется ответ в виде строки
    user_.increment_listening(1, 1);
    return "Answer on increment user listening";
}

std::string TcpServerUser::on_like_song(int song_id, int user_id, bool value) {
    // TODO() : вызывается метод класса User.like_song() и генерируется ответ в виде строки
    user_.like_song(1, 1, true);
    return "Answer on user like song";
}
