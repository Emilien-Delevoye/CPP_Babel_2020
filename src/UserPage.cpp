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
    User *user;

    _usersList = new QScrollArea(this);
    _usersList->setFixedWidth(360);
    _usersList->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    _usersList->setWidgetResizable( true );

    _usersWidget = new CustomWidget(this);
    _usersWidget->setProperty("name", "test");
    _usersList->setWidget(_usersWidget);
    _userVLayout = new QVBoxLayout(this);

    dynamic_cast<CustomMainWindow *>(parent)->test();
    for (int i = 0; i < 40; i++) {
        user = new User(this, "Jean" + std::to_string(i), "127.0.0.1");
        user->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        std::string tooltip = std::string("Display informations about ") + std::string("Jean") + std::to_string(i);
        user->setToolTip(tooltip.c_str());
        _users.push_back(user);
        user->setMinimumHeight(50);
        _userVLayout->addWidget(user );
    }
    _usersWidget->setLayout(_userVLayout);
    _hLayout = new QHBoxLayout(this);
    _hLayout->addWidget(_usersList);

    _callVLayout = new QVBoxLayout(this);

    _callWidget = new QWidget(this);
    _callButton = new CustomButton(this, "Call");
    _logOutButton = new CustomButton(this, "Log out");
    _logOutButton->setProperty("name", "logout");

    _callVLayout->addWidget(_callButton);
    _callVLayout->addWidget(_logOutButton);

    _callWidget->setLayout(_callVLayout);


    _hLayout->addWidget(_callWidget);

    setLayout(_hLayout);
    hide();
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