/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#ifndef BABEL_NETWORKUDP_HPP
#define BABEL_NETWORKTCP_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include "ReceiverUDP.hpp"
#include "SenderUDP.hpp"

class NetworkUDP : public ReceiverUDP, public SenderUDP {
protected:
    explicit NetworkUDP(const std::string &ipAddr, int port, bool first);
};

#endif //BABEL_NETWORKUDP_HPP