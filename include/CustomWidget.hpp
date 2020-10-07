/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#ifndef BABEL_CUSTOMWIDGET_HPP
#define BABEL_CUSTOMWIDGET_HPP

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QObject>

class CustomWidget : public QWidget {
    Q_OBJECT
    public:
        explicit CustomWidget(QWidget *parent = nullptr);
        void paintEvent(QPaintEvent *event) override;
    private:


};

#endif //BABEL_CUSTOMWIDGET_HPP
