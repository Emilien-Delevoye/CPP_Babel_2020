/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#ifndef BABEL_NETWORKTCP_HPP
#define BABEL_NETWORKTCP_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include "NetworkTCP/server/ServerTCP.hpp"
#include "NetworkTCP/server/InstanceClientTCP.hpp"

/*class NetworkTCP : public ServerTCP, public InstanceClientTCP {
protected:
    explicit NetworkTCP(const std::string &ipAddr, int port);
};*/

#endif //BABEL_NETWORKTCP_HPP
