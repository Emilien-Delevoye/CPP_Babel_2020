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

    connect(_logOutButton, SIGNAL(clicked()), this, SLOT( navToConnectionPage()));


    for (int i = 0; i < 40; i++) {
        user = new User(this, "Jean" + std::to_string(i), "127.0.0.1");
        user->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        std::string tooltip = std::string("Display informations about ") + std::string("Jean") + std::to_string(i);
        user->setToolTip(tooltip.c_str());
        _users.push_back(user);
        user->setMinimumHeight(50);
        _userVLayout->addWidget(user);
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

void UserPage::navToConnectionPage()
{
    auto * test = dynamic_cast<CustomMainWindow *>(parent());//->navToPage();
}

CustomButton *UserPage::getLogOutButton() const
{
    return _logOutButton;
}
