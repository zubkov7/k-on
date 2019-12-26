#include <sstream>

#include "db_worker_user.h"
#include "utils.h"

DbWorkerUser::DbWorkerUser() {}

DbWorkerUser::~DbWorkerUser() {}

std::string DbWorkerUser::login(const std::string &login, const std::string &pass, bool &status) const {
    std::stringstream query;
    query << "select Count(id) from user where login = '"
          << login
          << "' and password = '"
          << pass
          << "';";
    sql::ResultSet *result = db_wrapper_.execute_query(query.str());
    result->next();
    if (result->getInt(1) == 0) {  // Логин неверный
        status = false;
        return "";
    } else {  // Логин верный. Генерируем сессию для пользователя
        status = true;
        std::string session = get_hash(login + get_current_time() + pass);
        query.str("");
        query << "insert into session (login, session) values ('"
              << login
              << "', '"
              << session
              << "');";
        db_wrapper_.execute_query(query.str());
        return session;
    }
}

std::string DbWorkerUser::signup(const std::string &login, const std::string &pass, bool &status) const {
    try {
        std::stringstream query;
        query << "insert into user (login, password) values ('"
              << login
              << "', '"
              << pass
              << "');";
        db_wrapper_.execute(query.str());
        status = true;

        std::string session = get_hash(login + get_current_time() + pass);
        query.str("");
        query << "insert into session (login, session) values ('"
              << login
              << "', '"
              << session
              << "');";
        db_wrapper_.execute_query(query.str());
        return session;
    }
    catch (sql::SQLException &exception) {  // Логин занят
        status = false;
        return "";
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
              << " datetime = 'getdate()'"
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

int DbWorkerUser::get_user_id(const std::string &session, bool &status) const {
    std::stringstream query;
    query << "select login from session where session ='"
          << session
          << "';";

    sql::ResultSet *result = db_wrapper_.execute_query(query.str());

    if (result->rowsCount() == 0) {
        status = false;
        return 0;
    } else {
        status = true;
        result->next();
        std::string login = result->getString(1);
        query.str("");
        query << "select id from user where login ='"
              << login
              << "';";

        result = db_wrapper_.execute_query(query.str());
        result->next();
        return result->getInt(1);
    }
}

void DbWorkerUser::logout(const std::string &session) const {
    std::stringstream query;
    query << "delete from session where session = '"
          << session
          << "';";
    db_wrapper_.execute(query.str());
}

std::string DbWorkerUser::get_login(const std::string session, bool &status) const {
    std::stringstream query;
    query << "select login from session where session ='"
          << session
          << "';";

    sql::ResultSet *result = db_wrapper_.execute_query(query.str());

    if (result->rowsCount() == 0) {
        status = false;
        return "";
    } else {
        status = true;
        result->next();
        return result->getString(1);
    }
}
