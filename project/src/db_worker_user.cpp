#include "db_worker_user.h"

DbWorkerUser::DbWorkerUser() {
    // TODO() : определить конструктор
}

DbWorkerUser::~DbWorkerUser() {
    // TODO() : определить деструктор
}

user DbWorkerUser::get_user(int id) {
    // TODO() : выполнить нужный вопрос через DbWrapper
    db_wrapper_.execute_query("select * from user;");
    return user(0, "login", "password");
}

bool DbWorkerUser::login(const std::string &login, const std::string &pass) {
    // TODO() : выполнить нужный вопрос через DbWrapper
    db_wrapper_.execute_query("select * from user;");
    return false;
}

bool DbWorkerUser::register_user(const std::string &login, const std::string &pass) {
    // TODO() : выполнить нужный вопрос через DbWrapper
    db_wrapper_.execute_query("select * from user;");
    return false;
}

int DbWorkerUser::increment_listening(int song_id, int user_id) {
    // TODO() : выполнить нужный вопрос через DbWrapper
    db_wrapper_.execute_query("select * from user;");
    return 0;
}

bool DbWorkerUser::like_song(int song_id, int user_id, bool value) {
    // TODO() : выполнить нужный вопрос через DbWrapper
    db_wrapper_.execute_query("select * from user;");
    return false;
}

int DbWorkerUser::get_listening(int song_id, int user_id) {
    // TODO() : выполнить нужный вопрос через DbWrapper
    db_wrapper_.execute_query("select * from user;");
    return 0;
}

bool DbWorkerUser::get_like_song(int song_id, int user_id) {
    // TODO() : выполнить нужный вопрос через DbWrapper
    db_wrapper_.execute_query("select * from user;");
    return false;
}

bool DbWorkerUser::is_login_available(const std::string &login) {
    // TODO() : выполнить нужный вопрос через DbWrapper
    return false;
}
