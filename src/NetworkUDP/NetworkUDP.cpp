/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Network/NetworkUDP.hpp"

NetworkUDP::NetworkUDP(const std::string &ipAddr, int PortReceiver, int PortSender) : SenderUDP(ipAddr, PortSender), ReceiverUDP(ipAddr, PortReceiver)
{
    this->openServer();
}
