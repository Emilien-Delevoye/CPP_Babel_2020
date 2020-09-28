/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#ifndef B_CPP_500_LIL_5_1_BABEL_CYPRIEN_RICQUE_QTMAINWINDOW_H
#define B_CPP_500_LIL_5_1_BABEL_CYPRIEN_RICQUE_QTMAINWINDOW_H

#include <QApplication>
#include <QMainWindow>

class QTMainWindow : public QMainWindow {
    public:
        QTMainWindow(QWidget *parent = nullptr, const QString &title = "Window");
        ~QTMainWindow();
    private:

};

#endif //B_CPP_500_LIL_5_1_BABEL_CYPRIEN_RICQUE_QTMAINWINDOW_H
