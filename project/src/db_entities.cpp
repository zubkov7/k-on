#include "db_entities.h"

bool user::operator==(const user &a) const {
    return id == a.id && login == a.login && pass == a.pass;
}