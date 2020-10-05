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

class Users {
    int id;
    std::string name;
    std::string ip;
    short port;
};

struct UserType {
    int id;
    std::string name;
};

#endif //BABEL_USERS_HPP
