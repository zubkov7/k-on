#ifndef PROJECT_INCLUDE_DB_WRAPPER_H_
#define PROJECT_INCLUDE_DB_WRAPPER_H_

#include <iostream>
#include <sqlite3.h>

class DbWrapper {
public:
    DbWrapper();
    ~DbWrapper();

    void *make_request(const std::string &request);

private:
    sqlite3 *data_base;
};

#endif  // PROJECT_INCLUDE_DB_WRAPPER_H_
