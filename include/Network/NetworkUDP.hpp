/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_NETWORKUDP_HPP
#define BABEL_NETWORKUDP_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include "ServerUDP.hpp"
#include "ClientUDP.hpp"

class NetworkUDP : public ServerUDP, public ClientUDP {
protected:
    explicit NetworkUDP(const std::string &ipAddr, int port, bool first);
};

#endif //BABEL_NETWORKUDP_HPP
