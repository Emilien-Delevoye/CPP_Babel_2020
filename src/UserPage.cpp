/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#include "UserPage.hpp"

UserPage::UserPage(QWidget *parent) : QWidget(parent)
{
    User *user;
    _userVLayout = new QVBoxLayout(this);
    _callVLayout = new QVBoxLayout(this);
    _usersWidget = new QWidget(this);
    _callWidget = new QWidget(this);
    _hLayout = new QHBoxLayout(this);
    _callButton = new CustomButton(this, "Call");
    _logOutButton = new CustomButton(this, "Log out");

    for (int i = 0; i < 10; i++) {
        user = new User(this, "Jean" + std::to_string(i), "127.0.0.1");
        _users.push_back(user);
        _userVLayout->addWidget(user);
    }

    _callVLayout->addWidget(_callButton);
    _callVLayout->addWidget(_logOutButton);

    _usersWidget->setLayout(_userVLayout);
    _callWidget->setLayout(_callVLayout);

    _hLayout->addWidget(_usersWidget);
    _hLayout->addWidget(_callWidget);
    setLayout(_hLayout);
    hide();
}

UserPage::~UserPage()
{

}