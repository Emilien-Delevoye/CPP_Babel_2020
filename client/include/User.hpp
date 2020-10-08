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

#include "CustomButton.hpp"

class User : public CustomButton {
    Q_OBJECT
    public:
        explicit User(QWidget *parent = nullptr, const std::string &login = "login", const std::string &ip = "ip", short port = -1, int id = -1);
        std::string getLogin() const;
        std::string getIP() const;
        short getPort() const;
        int getID() const;
    private:
        std::string _login;
        std::string _ip;
        short _port;
        int _id;

};

#endif //BABEL_USER_HPP
