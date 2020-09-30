/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_INETWORK_HPP
#define BABEL_INETWORK_HPP

#include <string>
#include <vector>
#include <boost/asio/buffer.hpp>

class IClientUDP {
public:
    explicit IClientUDP(const std::string &ipAddr, int port) {
        this->_ipAddress = ipAddr;
        this->_port = port;
    }
    virtual void sendToServer(std::vector<unsigned char> in, size_t frameSize) = 0;
protected:
    std::string _ipAddress;
    int _port;
};

class IServerUDP {
public:
    explicit IServerUDP(const std::string &ipAddr, int port) {
        this->_ipAddress = ipAddr;
        this->_port = port;
    }
    virtual void openServer() = 0;
    virtual std::vector<unsigned char> getFromUDP() = 0;
protected:
    std::string _ipAddress;
    int _port;
};

#endif //BABEL_INETWORK_HPP
