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
//#include "../../../../../.conan/data/sqlite_orm/1.5/bincrafters/stable/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include/sqlite_orm/sqlite_orm.h" // FIXME

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
    // Password ?
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

    std::string getName(int id) {return storage.get<User>(id).name;}
    std::string getIP(int id) {return storage.get<User>(id).ip;}
    short getPort(int id) {return storage.get<User>(id).port;}

    std::vector<std::tuple<int, std::string, std::string, short>> getAllData();
private:
    decltype(make_storage_query()) storage;

};



#endif //BABEL_USERS_HPP
