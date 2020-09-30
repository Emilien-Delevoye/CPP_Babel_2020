/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#ifndef BABEL_USERPAGE_HPP
#define BABEL_USERPAGE_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <vector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSizePolicy>
#include "CustomLineEdit.hpp"
#include "CustomButton.hpp"
#include "enum.hpp"
#include "User.hpp"

class UserPage : public QWidget {
    Q_OBJECT
    public:
        UserPage(QWidget *parent = nullptr);
        ~UserPage();
    private:
        std::vector<User *> _users;
        QHBoxLayout *_hLayout;
        QWidget *_usersWidget;
        QWidget *_callWidget;
        QVBoxLayout *_userVLayout;
        QVBoxLayout *_callVLayout;
        CustomButton *_callButton;
        CustomButton *_logOutButton;
};

#endif //BABEL_USERPAGE_HPP
