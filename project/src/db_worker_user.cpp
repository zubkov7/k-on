#include <sstream>

#include "db_worker_user.h"

DbWorkerUser::DbWorkerUser() {}

DbWorkerUser::~DbWorkerUser() {}

bool DbWorkerUser::login(const std::string &login, const std::string &pass) const {
    std::stringstream query;
    query << "select Count(id) from user where login = '"
          << login
          << "' and password = '"
          << pass
          << "';";
    sql::ResultSet *result = db_wrapper_.execute_query(query.str());
    result->next();
    return result->getInt(1) != 0;
}

bool DbWorkerUser::sign_up(const std::string &login, const std::string &pass) const {
    try {
        std::stringstream query;
        query << "insert into user (login, password) values ('"
              << login
              << "', '"
              << pass
              << "');";
        db_wrapper_.execute(query.str());
        return true;
    }
    catch (sql::SQLException &exception) {  // Логин занят
        return false;
    }

}

int DbWorkerUser::increment_listening(int song_id, int user_id) const {
    std::stringstream query;
    query << "select count from listen where song_id = "
          << song_id
          << " and user_id = "
          << user_id
          << ";";
    sql::ResultSet *result = db_wrapper_.execute_query(query.str());
    query.str("");
    if (result->rowsCount() == 0) {  // Если записи не существует, то создаем ее
        query << "insert into listen (song_id, user_id, count) "
              << " values ("
              << song_id
              << ", "
              << user_id
              << ", 1);";
        db_wrapper_.execute(query.str());
        return 1;
    } else {  // Меняем значение у записи
        result->next();
        int count = result->getInt(1);
        query << "update listen set count = count + 1 where song_id = "
              << song_id
              << " and user_id = "
              << user_id
              << ";";
        db_wrapper_.execute(query.str());
        return count + 1;  // Возвращаем инкрементированное значение
    }
}

bool DbWorkerUser::like_song(int song_id, int user_id, bool value) const {
    std::stringstream query;
    query << "select value from like_dislike where song_id = "
          << song_id
          << " and user_id = "
          << user_id
          << ";";
    sql::ResultSet *result = db_wrapper_.execute_query(query.str());
    query.str("");
    if (result->rowsCount() == 0) {  // Если записи не существует, то создаем ее
        query << "insert into like_dislike (song_id, user_id, value) "
              << " values ("
              << song_id
              << ", "
              << user_id
              << ", "
              << value
              << ");";
        db_wrapper_.execute(query.str());
        return value;
    } else {  // Меняем значение у существующей записи
        query << "update like_dislike set value = "
              << value
              << " where song_id = "
              << song_id
              << " and user_id = "
              << user_id
              << ";";
        db_wrapper_.execute(query.str());
        return value;
    }
}

bool DbWorkerUser::is_song_exists(int song_id) const {
    std::stringstream query;
    query << "select Count(id) from song where id = "
          << song_id
          << ";";
    sql::ResultSet *result = db_wrapper_.execute_query(query.str());
    result->next();
    return result->getInt(1) != 0;
}

bool DbWorkerUser::is_user_exists(int user_id) const {
    std::stringstream query;
    query << "select Count(id) from user where id = "
          << user_id
          << ";";
    sql::ResultSet *result = db_wrapper_.execute_query(query.str());
    result->next();
    return result->getInt(1) != 0;
}
