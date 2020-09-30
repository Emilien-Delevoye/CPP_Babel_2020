/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#include "CustomMainWindow.hpp"

CustomMainWindow::CustomMainWindow(QWidget *parent, const QString &title) : QMainWindow(parent)
{
    setWindowTitle(title);

    _userPage = new UserPage(this);

    _connectionPage = new ConnectionPage(this);
    connect(_connectionPage->getConnectButton(), SIGNAL(clicked()), this, SLOT(navToUserPage()));

    setCentralWidget(_connectionPage);
    _connectionPage->show();
    centered();
}

CustomMainWindow::~CustomMainWindow()
{

}

void CustomMainWindow::navToUserPage()
{
    _connectionPage->hide(); //if success//
    setCentralWidget(_userPage);
    _userPage->show();
}

void CustomMainWindow::centered()
{
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();
    int x = (screenWidth - 500) / 2;
    int y = (screenHeight - 200) / 2;

    move(x, y);
}

void CustomMainWindow::test()
{
    qDebug() << "Dynamic_cast functional";
};