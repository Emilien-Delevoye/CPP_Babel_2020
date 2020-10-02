/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "NetworkUDP/NetworkUDP.hpp"

NetworkUDP::NetworkUDP(const std::string &ipAddr, int port, bool first) : SenderUDP(ipAddr, port), ReceiverUDP(ipAddr, port)
{
    if (first)
        std::cout << "Normalement c'est le first" << std::endl;
    this->openServer();
}
