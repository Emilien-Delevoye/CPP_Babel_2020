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
    _pages = new QStackedWidget(this);

    connect(_connectionPage->getConnectButton(), &QPushButton::clicked, [=]() {
        navToUserPage();
    });
    connect(_userPage->getLogOutButton(), &QPushButton::clicked, [=]() {
        navToConnectionPage();
    });
    _pages->addWidget(_userPage);
    _pages->addWidget(_connectionPage);

    setCentralWidget(_pages);
    _pages->setCurrentWidget(_connectionPage);
}

CustomMainWindow::~CustomMainWindow()
{

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

void CustomMainWindow::navToUserPage()
{
    _pages->setCurrentWidget(_userPage);
}

void CustomMainWindow::navToConnectionPage()
{
    _pages->setCurrentWidget(_connectionPage);
}
