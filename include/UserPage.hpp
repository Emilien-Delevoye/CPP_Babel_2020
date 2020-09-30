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
#include "CustomLineEdit.hpp"
#include "CustomButton.hpp"
#include "enum.hpp"


class UserPage : public QWidget {
    public:
        UserPage(QWidget *parent = nullptr);
        ~UserPage();
    private:
        QPushButton *_button;
};

#endif //BABEL_USERPAGE_HPP
