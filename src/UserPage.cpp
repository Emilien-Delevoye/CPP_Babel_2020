/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#include "UserPage.hpp"

UserPage::UserPage(QWidget *parent) : QWidget(parent)
{
    _userLogin = new CustomText(this);
    _userIP = new CustomText(this);
    _callWidgetBottom = new CustomWidget(this);
    _callWidgetTop = new CustomWidget(this);
    _callVLayoutTop = new QVBoxLayout(_callWidgetTop);
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
    _timer->setInterval(1000);
    _elapsedSeconds = 0;
    connect(_timer, &QTimer::timeout, [&]() {
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
    _userLogin->setText("login");
    _userLogin->setProperty("name", "userLogin");
    _userIP->setText("127.0.0.1");
    _userIP->setProperty("name", "userIP");
    _timerText->setProperty("name", "timerText");
    _usersWidget->setProperty("name", "userWidget");
    _usersList->setWidget(_usersWidget);
    _callWidgetBottom->setProperty("name", "callWidgetBottom");

    _usersWidget->setLayout(_userVLayout);
    _hLayout->addWidget(_usersList);
    _callVLayoutTop->addWidget(_userLogin);
    _callVLayoutTop->addWidget(_userIP);
    _callVLayoutTop->addWidget(_timerText);
    _callVLayoutTop->addWidget(_callButton);
    _callVLayoutTop->addWidget(_hangUpButton);
    _callVLayoutTop->setAlignment(Qt::AlignCenter);
    _callWidgetTop->setLayout(_callVLayoutTop);
    _callHLayoutBottom->addWidget(_logOutButton);
    _callWidgetBottom->setLayout(_callHLayoutBottom);
    _callVLayout->addWidget(_callWidgetTop);
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

void UserPage::init(const std::vector<User *>& _users)
{
    for (auto user : _users) {
        _userVLayout->addWidget(user);
    }
    _userLogin->hide();
    _userIP->hide();
    _callButton->hide();
    _hangUpButton->hide();
}

void UserPage::setUserInfo(const std::string &login, const std::string &ip)
{
    _userLogin->setText(QString::fromStdString(login));
    _userIP->setText(QString::fromStdString(ip));
    _callButton->setText(QString::fromStdString("Call ") + QString::fromStdString(login));

    _userLogin->show();
    _userIP->show();
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

