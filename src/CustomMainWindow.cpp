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
    _mainWidget->setFixedWidth(500);
    _mainWidget->setMaximumHeight(140);
    _vLayout = new QVBoxLayout(_mainWidget);
    _formWidget = new QWidget(_mainWidget);
    _formLayout = new QFormLayout(_formWidget);
    _lineEdits[HOME_IP_LINE_EDIT] = new CustomLineEdit(_mainWidget);
    _lineEdits[HOME_LOGIN_LINE_EDIT] = new CustomLineEdit(_mainWidget);
    _lineEdits[HOME_PASSWORD_LINE_EDIT] = new CustomLineEdit(_mainWidget);
    _lineEdits[HOME_PASSWORD_LINE_EDIT]->setEchoMode(QLineEdit::Password);
    _formLayout->addRow(formValue[HOME_IP_TEXT], _lineEdits[HOME_IP_LINE_EDIT]);
    _formLayout->addRow(formValue[HOME_LOGIN_TEXT], _lineEdits[HOME_LOGIN_LINE_EDIT]);
    _formLayout->addRow(formValue[HOME_PASSWORD_TEXT], _lineEdits[HOME_PASSWORD_LINE_EDIT]);
    _connectButton = new CustomButton(_mainWidget, "Connect");
    _connectButton->setToolTip("Establish the connection with the server");
    _formWidget->setLayout(_formLayout);
    _vLayout->addWidget(_formWidget);
    _vLayout->addWidget(_connectButton);
    _mainWidget->setLayout(_vLayout);
    setCentralWidget(_mainWidget);
    connect(_connectButton, SIGNAL(clicked(bool)), this, SLOT(direBonjour(bool)));

    centered();
}

CustomMainWindow::~CustomMainWindow()
{

}

void CustomMainWindow::direBonjour(bool b)
{
    qDebug() << "Hello";
    _connectButton->hide();
    _formWidget->hide();
}

void CustomMainWindow::centered()
{
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();
    int x = (screenWidth - 500) / 2;
    int y = (screenHeight - 200) / 2;

    move(x, y);
};
