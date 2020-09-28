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
    virtual void init(const std::string& IpAddressIn, int portIn) = 0;
    virtual void createSocket() = 0;
    virtual void sendData(std::string) = 0;
private:
    std::string ipAddress;
    int port;
};

class IServerUDP {
public:
    virtual void init(const std::string& IpAddressIn, int portIn) = 0;
    virtual void createSocket() = 0;
private:
    std::string ipAddress;
    int port;
};

#endif //BABEL_INETWORK_HPP
