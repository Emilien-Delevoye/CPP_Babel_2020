/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Network/NetworkUDP.hpp"

NetworkUDP::NetworkUDP(const std::string &ipAddr, int port, bool first) : ClientUDP(ipAddr, port), ServerUDP(ipAddr, port)
{
    if (first)
        std::cout << "Normalement c'est le first" << std::endl;
    this->openServer();
}
