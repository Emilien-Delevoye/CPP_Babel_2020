/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Network/NetworkUDP.hpp"

NetworkUDP::NetworkUDP(const std::string &ipAddr, int port, bool first) : ClientUDP(ipAddr, port), ServerUDP(ipAddr, port)
{
    if (first) {
        this->openServer();
        std::cout << "Création du endpoint" << std::endl;
        Sleep(10000);
    } else {
        //this->connectToServer();
        this->sendToServer("Pouet pouet");
        Sleep(500);
        this->sendToServer("idiot");
        //this->close();
    }
}
