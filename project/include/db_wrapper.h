#ifndef K_ON_DB_WRAPPER_H
#define K_ON_DB_WRAPPER_H


#include <iostream>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>


class DbWrapper {
public:
    explicit DbWrapper(const std::string &database, const std::string &host="localhost",
                       const std::string &user="root", const std::string &password="");
    DbWrapper();
    ~DbWrapper();

    bool execute(const std::string &request) const;
    sql::ResultSet *execute_query(const std::string &query) const;

private:
    sql::Connection *connection;
};


#endif  // K_ON_DB_WRAPPER_H
