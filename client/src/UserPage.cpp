/*!
 * @file UserPage.cpp
 * @brief UserPage class implementation
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 *
*/

#include "UserPage.hpp"

/*!
 * \brief The constructor of UserPage inherit of the CustomWidget class.
 * \param parent Parent widget (default value set to : nullptr)
 *
 * This constructor set all class variable, their property and their position thanks to the different layout.
*/

UserPage::UserPage(QWidget *parent) : CustomWidget(parent)
{
    _userLoginToCall = new CustomText(this);
    _userIPToCall = new CustomText(this);
    _callWidgetTop = new CustomWidget(this);
    _callWidgetBottom = new CustomWidget(this);
    _callWidgetMiddle = new CustomWidget(this);
    _callVLayoutTop = new QVBoxLayout(_callWidgetTop);
    _callVLayoutMiddle = new QVBoxLayout(_callWidgetMiddle);
    _callHLayoutBottom = new QHBoxLayout(_callWidgetBottom);
    _usersList = new QScrollArea(this);
    _usersWidget = new CustomWidget(this);
    _userVLayout = new QVBoxLayout(this);
    _hLayout = new QHBoxLayout(this);
    _callVLayout = new QVBoxLayout(this);
    _callWidget = new CustomWidget(this);
    _callButton = new CustomButton(this, "Call");
    _logOutButton = new CustomButton(this, "Log out");
    _hangUpButton = new CustomButton(this, "Hang up");
    _timer = new QTimer(this);
    _timerText = new CustomText(this);
    _actualTime = new CustomText(this);
    _userConnectedText = new CustomText(this);
    _serverIPText = new CustomText(this);
    _timer->setInterval(1000);
    _elapsedSeconds = 0;
    connect(_timer, &QTimer::timeout, [&]() {
        QString time1 = QTime::currentTime().toString();

        _elapsedSeconds++;
        int hours;
        int minutes;
        int seconds;

        hours = _elapsedSeconds / 3600;
        _elapsedSeconds %= 3600;

        minutes = _elapsedSeconds / 60;
        minutes %= 60;

        seconds = _elapsedSeconds;
        std::string concat = std::string((hours < 10 ? "0" : "") + std::to_string(hours)
            + ":" + std::string((minutes < 10 ? "0" : "") + std::to_string(minutes) +
            ":" + std::string((seconds < 10 ? "0" : "") + std::to_string(seconds))));
        _timerText->setText(concat.c_str());
        _actualTime->setText(time1);

    } );
    _timer->start();
    _timerText->hide();

    _usersList->setWidgetResizable( true);
    _usersList->setFixedWidth(360);
    _usersList->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn);
    _callButton->setProperty("name", "call");
    _logOutButton->setProperty("name", "logout");
    _hangUpButton->setProperty("name", "hangup");
    _hangUpButton->hide();
    _logOutButton->setToolTip("Disconnect yourself from the server");
    _userLoginToCall->setText("login");
    _userLoginToCall->setProperty("name", "userLogin");
    _userIPToCall->setText("127.0.0.1");
    _userIPToCall->setProperty("name", "userIP");
    _timerText->setProperty("name", "timerText");
    _usersWidget->setProperty("name", "userWidget");
    _usersList->setWidget(_usersWidget);
    _callWidgetTop->setProperty("name", "callWidgetTop");
    _callWidgetBottom->setProperty("name", "callWidgetBottom");

    _usersWidget->setLayout(_userVLayout);
    _hLayout->addWidget(_usersList);
    _callVLayoutTop->addWidget(_actualTime);
    _callVLayoutTop->addWidget(_serverIPText);
    _callVLayoutTop->addWidget(_userConnectedText);
    _callVLayoutTop->addWidget(_actualTime);
    _callVLayoutMiddle->addWidget(_userLoginToCall);
    _callVLayoutMiddle->addSpacing(20);
    _callVLayoutMiddle->addWidget(_userIPToCall);
    _callVLayoutMiddle->addSpacing(20);
    _callVLayoutMiddle->addWidget(_timerText);
    _callVLayoutMiddle->addSpacing(30);
    _callVLayoutMiddle->addWidget(_callButton);
    _callVLayoutMiddle->addWidget(_hangUpButton);
    _callVLayoutMiddle->setAlignment(Qt::AlignCenter);
    _callWidgetMiddle->setLayout(_callVLayoutMiddle);
    _callHLayoutBottom->addWidget(_logOutButton);
    _callWidgetBottom->setLayout(_callHLayoutBottom);
    _callVLayout->addWidget(_callWidgetTop);
    _callVLayout->addWidget(_callWidgetMiddle);
    _callVLayout->addWidget(_callWidgetBottom);
    _callWidget->setLayout(_callVLayout);
    _hLayout->addWidget(_callWidget);

    setLayout(_hLayout);
}

/*!
 * \brief This method return the _logoutButton member variable of UserPage.
*/

CustomButton *UserPage::getLogOutButton() const
{
    return _logOutButton;
}

/*!
 * \brief This method is called before any navigation on the UserPage
 * \param users CustomMainWindow _users variable reference.
 * \param serverIP CustomMainWindow _serverIP variable reference.
 * \param userLogin CustomMainWindow _userLogin variable reference.
 *
 * This method permit to replace, reset, hide or for example change some text or button.
 * Moreover, it set the CustomMainWindow variables users, serverIP and userLogin.
*/

void UserPage::init(const std::string &serverIP, const std::string &userLogin)
{
    _userLoginToCall->hide();
    _userIPToCall->hide();
    _callButton->hide();
    _hangUpButton->hide();

    _userConnectedText->setText(qPrintable(std::string("Connected as : " + userLogin).c_str()));
    _serverIPText->setText(qPrintable(std::string("Server IP : " + serverIP).c_str()));
}

/*!
 * \brief This method is called when a User is clicked.
 * \param login login of the clicked user.
 * \param ip ip of the clicked user
 *
 * This method permit update _userLoginToCall, _userIPToCall and _callButton texts
*/

void UserPage::setUserInfo(const std::string &login, const std::string &ip)
{
    _userLoginToCall->setText(qPrintable((login.c_str())));
    _userIPToCall->setText(qPrintable((ip.c_str())));
    _callButton->setText(qPrintable(std::string("Call " + login).c_str()));

    _userLoginToCall->show();
    _userIPToCall->show();
    _callButton->show();
}

/*!
 * \brief This method return the _hangUpButton member variable of UserPage.
*/

CustomButton *UserPage::getHangUpButton() const
{
    return _hangUpButton;
}

/*!
 * \brief This method return the _callButton member variable of UserPage.
*/

CustomButton *UserPage::getCallButton() const
{
    return _callButton;
}

/*!
 * \brief This method reset the _timer value which represent call duration and then show it to the user.
 * This method is call just before a call start.
*/

void UserPage::showTimer()
{
    _elapsedSeconds = 0;
    _timer->start();
    _timerText->setText("00:00:00");
    _timerText->show();
}

/*!
 * \brief This method hide the call timer
 * This method is call just after the user hang up the call
*/

void UserPage::hideTimer()
{
    _timerText->hide();
}

void UserPage::addUser(User *user)
{
    _userVLayout->addWidget(user);
    _users.push_back(user);
}

void UserPage::deleteUser(int id)
{
    int pos = 0;
    int savePos = -1;

    User *userToDelete;
    for (auto user : _users) {
        if (user->getID() == id) {
            savePos = pos;
            userToDelete = user;
        }
        pos++;
    }
    _userVLayout->removeWidget(userToDelete);
    delete userToDelete;
    _users.erase(_users.begin() + savePos);
}

bool UserPage::userExists(int id)
{
    for (auto & u : _users) {
        if (u->getID() == id)
            return true;
    }
    return false;
}

void UserPage::deleteAllUser()
{
    for (auto user : _users) {
        delete user;
    }
    _users.clear();
}
