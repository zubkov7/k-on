#include "db_worker.h"


DbWorker::DbWorker(const std::string &database) : wrapper(DbWrapper(database)) {}

DbWorker::~DbWorker() = default;

bool DbWorker::add_user(const std::string &login, const std::string &password) {
    sql::ResultSet *result = wrapper.execute_query(
            "select * from user "
            "where login = \'" + login + "\'"
    );

    if (result->next()) {
        return false;
    }

    wrapper.execute(
            "insert into user (login, password) "
            "values (\'" + login + "\', \'" + password + "\')"
    );
    return true;
}

bool DbWorker::add_song(const std::string &name, const std::string &author, const std::string &genre, int duration,
                        const std::string &date) {
    sql::ResultSet *result = wrapper.execute_query(
            "select * from song "
            "where name = \'" + name +
            "\' and author = \'" + author + "\'"
    );

    if (result->next()) {
        return false;
    }

    wrapper.execute(
            "insert into song (name, author, genre, duration, date) "
            "values (\'" + name + "\', \'" + author +
            "\', \'" + genre + "\', " + std::to_string(duration) +
            ", \'" + date + "\')"
    );
    return true;
}

bool DbWorker::add_like_dislike(int user_id, int song_id, bool value) {
    sql::ResultSet *result = wrapper.execute_query(
            "select * from like_dislike "
            "where user_id = " + std::to_string(user_id) +
            " and song_id = " + std::to_string(song_id)
    );

    if (result->next()) {
        wrapper.execute(
                "update like_dislike "
                "set value = " + std::to_string(value) +
                " where user_id = " + std::to_string(user_id) +
                " and song_id = " + std::to_string(song_id)
        );
    } else {
        wrapper.execute(
                "insert into like_dislike (user_id, song_id, value) "
                "values (" + std::to_string(user_id) + ", " + std::to_string(song_id) +
                ", " + std::to_string(value) + ")"
        );
    }
    return true;
}

bool DbWorker::add_listen(int user_id, int song_id, int count) {
    sql::ResultSet *result = wrapper.execute_query(
            "select * from listen "
            "where user_id = " + std::to_string(user_id) +
            " and song_id = " + std::to_string(song_id)
    );

    if (result->next()) {
        wrapper.execute(
                "update listen "
                "set count = " + std::to_string(count) +
                " where user_id = " + std::to_string(user_id) +
                " and song_id = " + std::to_string(song_id)
        );
    } else {
        wrapper.execute(
                "insert into listen (user_id, song_id, count) "
                "values (" + std::to_string(user_id) + ", " + std::to_string(song_id) +
                ", " + std::to_string(count) + ")"
        );
    }
    return true;
}
