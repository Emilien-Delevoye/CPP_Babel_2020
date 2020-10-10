/*!
 * @file AUser.hpp
 * @brief AUser abstract class prototype
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 * This class is useful to describe how the User can be implemented.<br>
 * This class is composed of getter which can be overwritten.
 *
*/

#ifndef BABEL_AUSER_HPP
#define BABEL_AUSER_HPP

#include <QObject>
#include "CustomButton.hpp"

class AUser : public CustomButton {
    Q_OBJECT
    public:
    explicit AUser(QWidget *parent = nullptr, const std::string &login = "login", const std::string &ip = "ip", int port = -1, int id = -1) : CustomButton(parent, QString(login.c_str())), _login(login), _ip(ip), _port(port), _id(id) {};
    virtual std::string getLogin() const = 0;
    virtual std::string getIP() const = 0;
    virtual int getPort() const = 0;
    virtual int getID() const = 0;

protected:
    std::string _login;
    std::string _ip;
    int _port;
    int _id;

};

#endif //BABEL_AUSER_HPP
