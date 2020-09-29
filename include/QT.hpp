/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#ifndef BABEL_QT_HPP
#define BABEL_QT_HPP

#include <QApplication>
#include "CustomMainWindow.hpp"
#include "CustomButton.hpp"

class QT {
    public:
        QT();
        QMainWindow *getMainWindow() const;
    private:
        QMainWindow *_mainWindow;

};

#endif //BABEL_QT_HPP
