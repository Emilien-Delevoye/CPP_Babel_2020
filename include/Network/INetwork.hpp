/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_INETWORK_HPP
#define BABEL_INETWORK_HPP

#include <string>

class IClientUDP {
public:
    explicit IClientUDP(const std::string &ipAddr, int port) {
        this->_ipAddress = ipAddr;
        this->_port = port;
    }
private:
    std::string _ipAddress;
    int _port;
};

class IServerUDP {
public:
    explicit IServerUDP(const std::string &ipAddr, int port) {
        this->_ipAddress = ipAddr;
        this->_port = port;
    }
private:
    std::string _ipAddress;
    int _port;
};

#endif //BABEL_INETWORK_HPP
