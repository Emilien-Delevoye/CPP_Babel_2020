/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#include "User.hpp"

User::~User()
{

}

User::User(QWidget *parent, const std::string &login, const std::string &ip) : CustomButton(parent, QString(login.c_str())), _login(login), _ip(ip)
{

}

std::string User::getLogin() const
{
    return _login;
}

std::string User::getIP() const
{
    return _ip;
}
