#include <db_wrapper.h>

#include <cppconn/driver.h>

DbWrapper::DbWrapper(const std::string &host, const std::string &user, const std::string &password) {
    sql::Driver *dr = get_driver_instance();
//    sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
    connection = dr->connect(host, user, password);
    std::cout << connection->isValid() << std::endl;
    connection->setSchema("mydb");
}

DbWrapper::~DbWrapper() {
    delete connection;
}

void *DbWrapper::make_request(const std::string &request) {
    return nullptr;
}


