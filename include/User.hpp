/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#ifndef BABEL_USER_HPP
#define BABEL_USER_HPP

#include <string>

class User {
    public:
        User(const std::string &login = "login", const std::string &ip = "ip");
        ~User();
        std::string getLogin() const;
        std::string getIP() const;
    private:
        std::string _login;
        std::string _ip;
};

#endif //BABEL_USER_HPP
