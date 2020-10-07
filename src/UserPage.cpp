/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#include "UserPage.hpp"

UserPage::UserPage(QWidget *parent) : QWidget(parent)
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
    _usersList->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
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

UserPage::~UserPage()
{

}

void UserPage::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}

CustomButton *UserPage::getLogOutButton() const
{
    return _logOutButton;
}

void UserPage::init(const std::vector<User *>& _users, const std::string &serverIP, const std::string &userLogin)
{
    for (auto user : _users) {
        _userVLayout->addWidget(user);
    }
    _userLoginToCall->hide();
    _userIPToCall->hide();
    _callButton->hide();
    _hangUpButton->hide();

    _userConnectedText->setText(QString::fromUtf8(std::string("Connected as : " + userLogin).c_str()));
    _serverIPText->setText(QString::fromUtf8(std::string("Server IP : " + serverIP).c_str()));
}

void UserPage::setUserInfo(const std::string &login, const std::string &ip)
{
    _userLoginToCall->setText(QString::fromUtf8(login.c_str()));
    _userIPToCall->setText(QString::fromUtf8(ip.c_str()));
    _callButton->setText(QString::fromUtf8("Call ") + QString::fromUtf8(login.c_str()));

    _userLoginToCall->show();
    _userIPToCall->show();
    _callButton->show();
}

CustomButton *UserPage::getHangUpButton() const
{
    return _hangUpButton;
}

CustomButton *UserPage::getCallButton() const
{
    return _callButton;
}

void UserPage::showTimer()
{
    _elapsedSeconds = 0;
    _timer->start();
    _timerText->setText("00:00:00");
    _timerText->show();
}

void UserPage::hideTimer()
{
    _timerText->hide();
}

