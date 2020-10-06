/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/


#ifndef BABEL_USERS_HPP
#define BABEL_USERS_HPP

#include <string>
#include <sqlite3.h>
#include <sqlite_orm/sqlite_orm.h>
#include <iostream>
//#include "../../../../../.conan/data/sqlite_orm/1.5/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include/sqlite_orm/sqlite_orm.h"

#define QUERY make_storage("select.sqlite", \
    make_table("Users", \
    make_column("ID", &User::id, primary_key()), \
    make_column("NAME", &User::name), \
    make_column("IP", &User::ip), \
    make_column("PORT", &User::port)))

using namespace sqlite_orm;

struct User {
    int id;
    std::string name;
    std::string ip;
    short port;
};

template <typename... Args>
auto make_storage_query() {
    return QUERY;
}

class DataBase {
public:
    DataBase();
    int addRow(std::string name, std::string ip, short port);
    void removeRow(int id);

private:
    decltype(make_storage_query()) storage;

};



#endif //BABEL_USERS_HPP
