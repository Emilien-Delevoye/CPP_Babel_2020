/*!
 * @file User.cpp
 * @brief User class implementation
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 *
*/

#include "User.hpp"

/*!
 * \brief The constructor of User inherit of the CustomButton class because we consider it as a button (to call some functions).
 * \param parent Parent widget (default value set to : nullptr)
 * \param login User's login
 * \param ip User's ip
 *
*/

User::User(QWidget *parent, const std::string &login, const std::string &ip) : CustomButton(parent, QString(login.c_str())), _login(login), _ip(ip)
{

}

/*!
* \brief This method return the _login member variable of User class.
*/

std::string User::getLogin() const
{
    return _login;
}

/*!
* \brief This method return the _ip member variable of User class.
*/

std::string User::getIP() const
{
    return _ip;
}
