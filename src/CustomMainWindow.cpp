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

    _connectionPage = new ConnectionPage(this);
    _userPage = new UserPage(this);
    _pages = new QStackedWidget(this);

    _callInProgress = false;

    connect(_connectionPage->getConnectButton(), &QPushButton::clicked, [=]() {
        _connectionPage->fillUserInfo(_serverIP, _userLogin, _userPassword);
        if (checkField()) {
            navToUserPage();
            qDebug() << "Connected as " << QString::fromStdString(_userLogin) << " with Ip address " << QString::fromStdString(_serverIP) << endl;
        }
    });
    connect(_userPage->getLogOutButton(), &QPushButton::clicked, [=]() {
        if (!_callInProgress) {
            _connectionPage->emptyPassword();
            navToConnectionPage();
        }
    });
    connect(_userPage->getCallButton(), &QPushButton::clicked, [=]() {
        _callInProgress = true;
        _userPage->showTimer();
        _userPage->getCallButton()->hide();
        _userPage->getHangUpButton()->show();
    });
    connect(_userPage->getHangUpButton(), &QPushButton::clicked, [=]() {
        _callInProgress = false;
        _userPage->hideTimer();
        _userPage->getHangUpButton()->hide();
        _userPage->getCallButton()->show();
    });
    _pages->addWidget(_userPage);
    _pages->addWidget(_connectionPage);

    setCentralWidget(_pages);
    navToConnectionPage();
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
    User *user;
    for (int i = 0; i < 10; i++) {
        user = new User(_userPage, "Jean" + std::to_string(i), std::string("127.0.0.") + std::to_string(i));
        user->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        std::string tooltip = std::string("Display informations about ") + std::string("Jean") + std::to_string(i);
        user->setToolTip(tooltip.c_str());
        user->setMinimumHeight(50);
        _users.push_back(user);
        connect(user, &QPushButton::clicked, [=]() {
            if (!_callInProgress) {
                _otherIP = user->getIP();
                _otherLogin = user->getLogin();
                _userPage->setUserInfo(_otherLogin, _otherIP);
            }
        });
    }
    _userPage->init(_users, _serverIP, _userLogin);
    _pages->setCurrentWidget(_userPage);
}

void CustomMainWindow::navToConnectionPage()
{
    for (auto userToDelete : _users)
    {
        delete userToDelete;
    }
    _users.clear();

    _connectionPage->init();
    _pages->setCurrentWidget(_connectionPage);
}

bool CustomMainWindow::checkField() const
{
    if (_serverIP.empty()) {
        _connectionPage->setError("Error: Server field is empty.");
        return false;
    } else if (_userLogin.empty()) {
        _connectionPage->setError("Error: Login field is empty.");
        return false;
    } else if (_userPassword.empty()) {
        _connectionPage->setError("Error: Password field is empty.");
        return false;
    }
    return true;
}
