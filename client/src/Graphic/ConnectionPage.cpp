/*!
 * @file ConnectionPage.cpp
 * @brief ConnectionPage class implementation
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
*/

#include "Graphic/ConnectionPage.hpp"

/*!
 * \brief The constructor of ConnectionPage inherit of the CustomWidget class (in order to be customisable).
 * \param parent parent widget (default value set to : nullptr)
 *
 * This constructor set all ConnectionPage variable, their property and their position thanks to the different layout.
*/

ConnectionPage::ConnectionPage(QWidget *parent) : CustomWidget(parent)
{
    _connectButton = new CustomButton(this, "Connect");
    _lineEdits[HOME_IP_LINE_EDIT] = new CustomLineEdit(this);
    _lineEdits[HOME_PORT_LINE_EDIT] = new CustomLineEdit(this);
    _lineEdits[HOME_LOGIN_LINE_EDIT] = new CustomLineEdit(this);
    _lineEdits[HOME_PASSWORD_LINE_EDIT] = new CustomLineEdit(this);
    _vLayout = new QVBoxLayout(this);
    _formLayout = new QFormLayout(this);
    _formWidget = new CustomWidget(this);
    _errorMessage = new CustomText(this, "Error :");

    _connectButton->setProperty("name", "login");
    _connectButton->setToolTip("Establish the connection with the server");
    _errorMessage->setProperty("name", "error");
    _lineEdits[HOME_PASSWORD_LINE_EDIT]->setEchoMode(QLineEdit::Password);
    _errorMessage->hide();

    _formWidget->setMinimumWidth(300);
    _formLayout->addRow(formValue[HOME_IP_TEXT], _lineEdits[HOME_IP_LINE_EDIT]);
    _formLayout->setSpacing(16);
    _formLayout->addRow(formValue[HOME_PORT_TEXT], _lineEdits[HOME_PORT_LINE_EDIT]);
    _formLayout->setSpacing(16);
    _formLayout->addRow(formValue[HOME_LOGIN_TEXT], _lineEdits[HOME_LOGIN_LINE_EDIT]);
    _formLayout->setSpacing(16);
    _formLayout->addRow(formValue[HOME_PASSWORD_TEXT], _lineEdits[HOME_PASSWORD_LINE_EDIT]);

    _formWidget->setLayout(_formLayout);

    _vLayout->setMargin(300);
    _vLayout->addWidget(_formWidget, 0,Qt::AlignCenter);
    _vLayout->setSpacing(32);
    _vLayout->addWidget(_errorMessage, 0,Qt::AlignCenter);
    _vLayout->setSpacing(32);
    _vLayout->addWidget(_connectButton, 0,Qt::AlignCenter);
    setLayout(_vLayout);
}

/*!
* \brief This method return the _connectButton member variable of ConnectionPage class.
*/

CustomButton *ConnectionPage::getConnectButton() const
{
    return _connectButton;
}

/*!
 * \brief This method is called before any navigation on the ConnectionPage.
 *
 * This method permit to replace, reset, hide or for example change some text or button.
*/

void ConnectionPage::init()
{
    _errorMessage->hide();
}

/*!
 * \brief This method is called once the connectedButton is pressed.
 *
 * This method permit to fill CustomMainWindow member variables _serverIP, _userLogin and _userPassword with the corresponding field.
*/

void ConnectionPage::fillUserInfo(std::string &serverIp, std::string &serverPort, std::string &userLogin, std::string &userPassword) const
{
    serverIp = qPrintable(_lineEdits[HOME_IP_LINE_EDIT]->text());
    serverPort = qPrintable(_lineEdits[HOME_PORT_LINE_EDIT]->text());
    userLogin = qPrintable(_lineEdits[HOME_LOGIN_LINE_EDIT]->text());
    userPassword = qPrintable(_lineEdits[HOME_PASSWORD_LINE_EDIT]->text());
}

/*!
 * \brief This method is called once the user pressed the logout button of the UserPage.
 *
 * This method permit to clear the password field.
*/

void ConnectionPage::emptyPassword()
{
    _lineEdits[HOME_PASSWORD_LINE_EDIT]->clear();
}

/*!
 * \brief This method is called once an error occurred during connection. (example: empty field)
 * \param errorMessage A string that represents the error that occurred.
 *
 * This method permit show the text error to the user.
*/

void ConnectionPage::setError(const std::string &errorMessage)
{
    _errorMessage->setText(qPrintable(errorMessage.c_str()));
    _errorMessage->show();
}