/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#ifndef BABEL_CUSTOMBUTTON_HPP
#define BABEL_CUSTOMBUTTON_HPP

#include <QPushButton>

class CustomButton : QPushButton {
    public:
        CustomButton(QWidget *parent = nullptr, const QString &title = "toto");
        ~CustomButton();
    private:
};

#endif //BABEL_CUSTOMBUTTON_HPP
