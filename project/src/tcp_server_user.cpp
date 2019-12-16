//
// Created by andrey on 23.11.2019.
//

#include "tcp_server_user.h"

TcpServerUser::TcpServerUser(unsigned short port) : TcpServer(port) {}

std::string TcpServerUser::handle_request(const std::string &request) const {
    // TODO() : по запросу вызывает нужные методы (сервера) on_get_user...
    if (request == "/login/") {
        return on_login("login", "password");
    }
    if (request == "/register/") {
        return on_register("admin", "password");
    }
    if (request == "/incrementlistening/") {
        return on_inc_listening(1, 1);
    }
    if (request == "/likesong/") {
        return on_like_song(1, 1, false);
    }

    return "Wrong command!";
}

std::string TcpServerUser::on_login(const std::string &login, const std::string &pass) const {
    // TODO() : вызывается метод класса UserSystem.login() и генерируется ответ в виде строки
    return user_system_.login(login, pass);
}

std::string TcpServerUser::on_register(const std::string &login, const std::string &pass) const {
    // TODO() : вызывается метод класса UserSystem.sign_up() и генерируется ответ в виде строки
    return user_system_.register_user(login, pass);
}

std::string TcpServerUser::on_inc_listening(int song_id, int user_id) const {
    // TODO() : вызывается метод класса UserSystem.increment_listening() и генерируется ответ в виде строки
    return user_system_.increment_listening(song_id, user_id);
}

std::string TcpServerUser::on_like_song(int song_id, int user_id, bool value) const {
    // TODO() : вызывается метод класса UserSystem.like_song() и генерируется ответ в виде строки
    return user_system_.like_song(song_id, user_id, value);
}
