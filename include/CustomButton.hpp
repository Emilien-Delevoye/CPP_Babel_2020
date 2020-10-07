/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#ifndef BABEL_CUSTOMBUTTON_HPP
#define BABEL_CUSTOMBUTTON_HPP

#include <QPushButton>

class CustomButton : public QPushButton {
    Q_OBJECT
    public:
        explicit CustomButton(QWidget *parent = nullptr, const QString &text = "text");
    private:
};

#endif //BABEL_CUSTOMBUTTON_HPP
