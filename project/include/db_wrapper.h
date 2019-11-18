#ifndef PROJECT_INCLUDE_DB_WRAPPER_H_
#define PROJECT_INCLUDE_DB_WRAPPER_H_

#include <iostream>
#include <cppconn/connection.h>

class DbWrapper {
public:
    explicit DbWrapper(const std::string &host="localhost", const std::string &user="root",
                       const std::string &password="");
    ~DbWrapper();

    void *make_request(const std::string &request);

private:
    sql::Connection *connection;
};

#endif  // PROJECT_INCLUDE_DB_WRAPPER_H_
