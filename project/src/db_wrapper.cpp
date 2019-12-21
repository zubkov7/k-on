#include <cppconn/driver.h>
#include <cppconn/statement.h>

#include "db_wrapper.h"


DbWrapper::DbWrapper(const std::string &database, const std::string &host,
                     const std::string &user, const std::string &password) {
    sql::Driver *driver = get_driver_instance();
    connection = driver->connect(host, user, password);
    connection->setSchema(database);
}

DbWrapper::~DbWrapper() {
    connection->close();
    delete connection;
}

bool DbWrapper::execute(const std::string &request) const {
    sql::Statement *statement = connection->createStatement();

    return statement->execute(request);
}

sql::ResultSet *DbWrapper::execute_query(const std::string &query) const {
    try {
        sql::Statement *statement = connection->createStatement();
        sql::ResultSet *result = statement->executeQuery(query);

        delete statement;
        return result;
    }
    catch (sql::SQLException &e) {
        std::cout << e.what() << std::endl;
    }

}

DbWrapper::DbWrapper() {
    sql::Driver *driver = get_driver_instance();
    connection = driver->connect("localhost", "root", "");
    connection->setSchema("test");
}
