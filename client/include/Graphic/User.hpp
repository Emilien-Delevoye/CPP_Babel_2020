/*!
 * @file User.hpp
 * @brief User class prototype
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 * This class is useful to describe how the User is represented in our program.<br>
 * This class is composed of two methods (getter) and two member variables (login and ip).
 *
*/

#ifndef BABEL_USER_HPP
#define BABEL_USER_HPP

#include "Graphic/AUser.hpp"
#include <iostream>

class User : public AUser {
    Q_OBJECT
    public:
        User(QWidget *parent, const std::string &login, const std::string &ip, int port, int id);
        std::string getLogin() const override;
        std::string getIP() const override;
        int getPort() const override;
        int getID() const override;
};

#endif //BABEL_USER_HPP
