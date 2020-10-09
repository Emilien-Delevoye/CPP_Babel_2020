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
#include <utility>
#include "ADatabase.hpp"

#define QUERY make_storage("select.sqlite", \
    make_table("Users", \
    make_column("ID", &User::id, primary_key()), \
    make_column("LOGIN", &User::login), \
    make_column("PASSWORD", &User::password), \
    make_column("IP", &User::ip), \
    make_column("PORT", &User::port)))

using namespace sqlite_orm;

struct User {
    int id;
    std::string login;
    std::string password;
    std::string ip;
    short port;
};

template <typename... Args>
auto make_storage_query() {
    return QUERY;
}

//template<typename T>
class DataBase {
public:
    DataBase();
    int addRow(std::string name, std::string password, std::string ip, short port);
    void removeRow(int id);

    std::string getPassword(int id) {return storage.get<User>(id).password;}
    std::string getIP(int id) {return storage.get<User>(id).ip;}
    short getPort(int id) {return storage.get<User>(id).port;}

    std::vector<int> getIds() {return storage.select(&User::id);}
    std::vector<std::string> getLogins() {return storage.select(&User::login);}
    std::vector<std::string> getIPs() {return storage.select(&User::ip);}
    std::vector<short> getPorts() {return storage.select(&User::port);}

    std::string getPasswordFromLogin(std::string login);
    void removeRowFromLogin(std::string login);

    int getIdFromLogin(std::string login);
private:
    decltype(make_storage_query()) storage;

};

#endif //BABEL_USERS_HPP
