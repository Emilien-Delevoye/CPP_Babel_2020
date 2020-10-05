/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#include "Server.hpp"

[[noreturn]] Server::Server(std::string &ip, short port) : serverTCP_(ip, port)
{
    while (true) {
        if (serverTCP_.newClientConnected() or serverTCP_.newClientDisconnected()) {
            serverTCP_.sendMessageToAllClientsConnected();
        }
        if (serverTCP_.newMessageReveiced()) {
            serverTCP_.getNewMessageReveicedClientId();
            serverTCP_.sendMessageToClient(1);
        }
    }
}