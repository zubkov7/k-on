#include "User.h"

User::User() {
    user_ = user(1, "login", "password");
}

user User::get_user(int id) {
    // TODO() : выполнить DbWorker.get_user() и преобразовать из строки в структуру user
    db_worker_.get_user(1);
    return user(0, "login", "password");
}

bool User::login(const std::string &login, const std::string &pass) {
    // TODO() : выполнить DbWorker.login() и преобразовать из строки в bool
    db_worker_.login(login, pass);
    return true;
}

bool User::register_user(const std::string &login, const std::string &pass) {
    // TODO() : выполнить DbWorker.register_user() и преобразовать из строки в bool
    db_worker_.register_user(login, pass);
    return true;
}

int User::increment_listening(int song_id, int user_id) {
    // TODO() : выполнить DbWorker.increment_listening() и преобразовать из строки в int (текущее количество прослушиваний)
    db_worker_.increment_listening(song_id, user_id);
    return 7;
}

bool User::like_song(int song_id, int user_id, bool value) {
    // TODO() : выполнить DbWorker.get_user() и преобразовать из строки в bool (текущий лайк или дизлайк)
    db_worker_.like_song(song_id, user_id, value);
    return true;
}
