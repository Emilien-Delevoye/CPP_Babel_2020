/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/


#include "ConnectionPage.hpp"

ConnectionPage::ConnectionPage(QWidget *parent) : QWidget(parent)
{
    setFixedWidth(500);
    setMaximumHeight(120);

    _vLayout = new QVBoxLayout(this);
    _formLayout = new QFormLayout(this);
    _lineEdits[HOME_IP_LINE_EDIT] = new CustomLineEdit(this);
    _lineEdits[HOME_LOGIN_LINE_EDIT] = new CustomLineEdit(this);
    _lineEdits[HOME_PASSWORD_LINE_EDIT] = new CustomLineEdit(this);
    _lineEdits[HOME_PASSWORD_LINE_EDIT]->setEchoMode(QLineEdit::Password);
    _formLayout->addRow(formValue[HOME_IP_TEXT], _lineEdits[HOME_IP_LINE_EDIT]);
    _formLayout->addRow(formValue[HOME_LOGIN_TEXT], _lineEdits[HOME_LOGIN_LINE_EDIT]);
    _formLayout->addRow(formValue[HOME_PASSWORD_TEXT], _lineEdits[HOME_PASSWORD_LINE_EDIT]);
    _connectButton = new CustomButton(this, "Connect");
    _connectButton->setToolTip("Establish the connection with the server");
    _vLayout->addLayout(_formLayout);
    _vLayout->addWidget(_connectButton);
    setLayout(_vLayout);
    hide();
}

ConnectionPage::~ConnectionPage()
{
}

CustomButton *ConnectionPage::getConnectButton() const
{
    return _connectButton;
}
