/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#include "QTMainWindow.hpp"

QTMainWindow::QTMainWindow(QWidget *parent, const QString &title) : QMainWindow(parent)
{
    setWindowTitle(title);
}

QTMainWindow::~QTMainWindow()
{

};
