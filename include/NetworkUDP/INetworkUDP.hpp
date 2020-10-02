/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_INETWORKUDP_HPP
#define BABEL_INETWORKUDP_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include <string>
#include <vector>
#include <boost/asio/buffer.hpp>

class ISenderUDP {
public:
    explicit ISenderUDP(const std::string &ipAddr, int port) {
        this->_ipAddress = ipAddr;
        this->_port = port;
    }
    virtual void sendToServer(std::vector<unsigned char> in, size_t frameSize) = 0;
protected:
    std::string _ipAddress;
    int _port;
};

class IReceiverUDP {
public:
    explicit IReceiverUDP(const std::string &ipAddr, int port) {
        this->_ipAddress = ipAddr;
        this->_port = port;
    }
    virtual void openServer() = 0;
    virtual std::vector<unsigned char> getFromUDP() = 0;
protected:
    std::string _ipAddress;
    int _port;
};

#endif //BABEL_INETWORKUDP_HPP
