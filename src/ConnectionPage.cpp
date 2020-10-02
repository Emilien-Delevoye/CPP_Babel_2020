/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/


#include "ConnectionPage.hpp"
#include "UserPage.hpp"
#include "CustomMainWindow.hpp"

ConnectionPage::ConnectionPage(QWidget *parent) : QWidget(parent)
{
    _vLayout = new QVBoxLayout(this);
    _formLayout = new QFormLayout(this);
    _formWidget = new QWidget(this);
    _connectButton = new CustomButton(this, "Connect");

    _connectButton->setProperty("name", "login");
    _vLayout->setMargin(80);

    _lineEdits[HOME_IP_LINE_EDIT] = new CustomLineEdit(this);
    _lineEdits[HOME_LOGIN_LINE_EDIT] = new CustomLineEdit(this);
    _lineEdits[HOME_PASSWORD_LINE_EDIT] = new CustomLineEdit(this);
    _lineEdits[HOME_PASSWORD_LINE_EDIT]->setEchoMode(QLineEdit::Password);
    _formWidget->setMinimumWidth(300);
    _formLayout->addRow(formValue[HOME_IP_TEXT], _lineEdits[HOME_IP_LINE_EDIT]);
    _formLayout->setSpacing(16);
    _formLayout->addRow(formValue[HOME_LOGIN_TEXT], _lineEdits[HOME_LOGIN_LINE_EDIT]);
    _formLayout->setSpacing(16);
    _formLayout->addRow(formValue[HOME_PASSWORD_TEXT], _lineEdits[HOME_PASSWORD_LINE_EDIT]);
    _connectButton->setToolTip("Establish the connection with the server");


    _formWidget->setLayout(_formLayout);

    _vLayout->setMargin(300);
    _vLayout->addWidget(_formWidget, 0,Qt::AlignCenter);
    _vLayout->setSpacing(32);
    _vLayout->addWidget(_connectButton, 0,Qt::AlignCenter);
    setLayout(_vLayout);
}

ConnectionPage::~ConnectionPage()
{
}

void ConnectionPage::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}

CustomButton *ConnectionPage::getConnectButton() const
{
    return _connectButton;
}
