/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#include "Server.hpp"

[[noreturn]] Server::Server(std::string &ip, short port) : serverTCP_(ip, port)
{
    Communication com(Communication::UPDATE_CLIENTS);
    while (true) {
        if (serverTCP_.newClientDisconnected()) {
            //serverTCP_.sendMessageToAllClientsConnected(tmp);
        }
        if (serverTCP_.newClientConnected()) {
            //serverTCP_.sendMessageToAllClientsConnected(tmp);
        }

        /*
        if (serverTCP_.newMessageReceived()) {
            serverTCP_.getNewMessageReceivedClientId();
            serverTCP_.sendMessageToClient(1, msg);
        }
        sleep(2);*/
    }
}