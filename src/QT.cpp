/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#include "QT.hpp"

QT::QT() : _mainWindow(new CustomMainWindow(nullptr, "Babel"))
{

}

QMainWindow *QT::getMainWindow() const
{
    return _mainWindow;
}
