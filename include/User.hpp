/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#ifndef BABEL_USER_HPP
#define BABEL_USER_HPP

#include <string>
#include "CustomButton.hpp"

class User : public CustomButton {
    Q_OBJECT
    public:
        User(QWidget *parent, const std::string &login = "login", const std::string &ip = "ip");
        ~User();
        std::string getLogin() const;
        std::string getIP() const;
    private:
        std::string _login;
        std::string _ip;
};

#endif //BABEL_USER_HPP
