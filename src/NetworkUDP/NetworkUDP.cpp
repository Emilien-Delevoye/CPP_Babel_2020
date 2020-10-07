/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "NetworkUDP/NetworkUDP.hpp"

NetworkUDP::NetworkUDP(const std::string &ipAddr, int PortReceiver, int PortSender, Audio *audio) : SenderUDP(ipAddr, PortSender), ReceiverUDP(ipAddr, PortReceiver, audio)
{
    this->openServer();
}
