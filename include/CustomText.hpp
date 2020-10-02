/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#ifndef BABEL_CUSTOMTEXT_HPP
#define BABEL_CUSTOMTEXT_HPP

#include <QLabel>

class CustomText : public QLabel {
    Q_OBJECT
    public:
        CustomText(QWidget *parent = nullptr, const QString &text = "text");
    private:

};

#endif //BABEL_CUSTOMTEXT_HPP
