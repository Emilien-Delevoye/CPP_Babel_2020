/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#include "CustomMainWindow.hpp"
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
    _callWidget = new QWidget(this);
    _callButton = new CustomButton(this, "Call");
    _logOutButton = new CustomButton(this, "Log out");
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

void UserPage::init( std::vector<User *> _users)
{
    _usersList->setWidgetResizable( true);

    _callButton->setProperty("name", "call");
    _logOutButton->setProperty("name", "logout");
    _logOutButton->setToolTip("Disconnect yourself from the server");
    _userLogin->setText("login");
    _userLogin->setProperty("name", "userLogin");
    _userIP->setText("127.0.0.1");
    _userIP->setProperty("name", "userIP");
    _usersList->setFixedWidth(360);
    _usersList->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    _usersWidget->setProperty("name", "userWidget");
    _usersList->setWidget(_usersWidget);

    for (auto _user : _users) {
        _userVLayout->addWidget(_user);
    }

    _usersWidget->setLayout(_userVLayout);
    _hLayout->addWidget(_usersList);

    _callVLayoutTop->addWidget(_userLogin);
    _callVLayoutTop->addWidget(_userIP);
    _callVLayoutTop->addWidget(_callButton);
    _callWidgetTop->setLayout(_callVLayoutTop);
    _callHLayoutBottom->addWidget(_logOutButton);
    _callWidgetBottom->setLayout(_callHLayoutBottom);
    _callVLayout->addWidget(_callWidgetTop);
    _callVLayout->addWidget(_callWidgetBottom);
    _callWidget->setLayout(_callVLayout);
    _hLayout->addWidget(_callWidget);

    setLayout(_hLayout);
}

void UserPage::setUserInfo(const std::string &login, const std::string &ip)
{
    _userLogin->setText(QString::fromStdString(login));
    _userIP->setText(QString::fromStdString(ip));
}

