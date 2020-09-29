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
    _mainWidget = new QWidget(this);
    _mainWidget->setMinimumWidth(500);
    _vLayout = new QVBoxLayout(_mainWidget);

    _formLayout = new QFormLayout(_mainWidget);

    _lineEdits[HOME_IP_LINE_EDIT] = new CustomLineEdit(_mainWidget);
    _lineEdits[HOME_LOGIN_LINE_EDIT] = new CustomLineEdit(_mainWidget);
    _lineEdits[HOME_PASSWORD_LINE_EDIT] = new CustomLineEdit(_mainWidget);

    _formLayout->addRow(formValue[HOME_IP_TEXT], _lineEdits[HOME_IP_LINE_EDIT]);
    _formLayout->addRow(formValue[HOME_LOGIN_TEXT], _lineEdits[HOME_LOGIN_LINE_EDIT]);
    _formLayout->addRow(formValue[HOME_PASSWORD_TEXT], _lineEdits[HOME_PASSWORD_LINE_EDIT]);

    _vLayout->addLayout(_formLayout);

    _connectButton = new CustomButton(_mainWidget, "Connect");

    _vLayout->addWidget(_connectButton);

    _mainWidget->setLayout(_vLayout);

    setCentralWidget(_mainWidget);
}

CustomMainWindow::~CustomMainWindow()
{

};
