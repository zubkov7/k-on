#include <iostream>

#include <db_wrapper.h>

int main() {
    DbWrapper wrapper = DbWrapper();
    try {
        wrapper.execute("create table user ("
                        "id mediumint not null auto_increment,"
                        "login char(20) not null,"
                        "password char(20) not null,"
                        "primary key (login, password)"
                        ");");
    } catch (sql::SQLException &e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    wrapper.execute("insert into user (login, password) values"
                    "('alice', 'alice'), ('bob', 'bob'),"
                    "('nemo', 'nemo');");
    sql::ResultSet *res = wrapper.execute_query("select * from user;");

    while (res->next()) {
        std::cout << res->getInt("id") << ' ' << res->getString("login") << ' '
                  << res->getString("password") << std::endl;
    }

    return 0;
}
