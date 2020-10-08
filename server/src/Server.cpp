/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#include "Server.hpp"

Server::Server(std::string &ip, short port) : serverTCP_(ip, port)
{
    Communication com(Communication::UPDATE_CLIENTS);

}

[[noreturn]] void Server::run()
{
    while (true) {
        if (serverTCP_.isDisconnectedClients()) {
            auto disconnectedClients = serverTCP_.getDisconnectedClientsIds();
            for (int c : disconnectedClients)
                serverTCP_.sendMessageToAllClientsConnected(Communication(Communication::DISCONNECTED_USER, c).serialize());
        }

        if (serverTCP_.newMessageReceived()) {
            auto id = serverTCP_.getNewMessageReceivedClientId();
            auto msg = std::string("serverTCP_.cli");
            serverTCP_.getNewMessageReceivedClientId();
            serverTCP_.sendMessageToClient(1, msg);
        }
        sleep(2);
    }
}