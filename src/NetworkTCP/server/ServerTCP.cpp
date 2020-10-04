/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#include "NetworkTCP/server/ServerTCP.hpp"
#include <thread>

// Receive Msg -> client nb & msg
// Receive Msg from client -> msg
// Send Msg to (client, msg)
// Send Msg to all clients (msg)

/* On reçoit les demandes de call / raccrochage / décrochage */

std::deque<std::shared_ptr<InstanceClientTCP>> ServerTCP::Clients;

ServerTCP::ServerTCP(short port) : acceptor_(io_service_, tcp::endpoint(tcp::v4(), port)),
                                   socket_(io_service_) {
    handleConnections();
    std::cout << "Server Started! Listening on Port(" + std::to_string(port) + ")" << std::endl;
    io_service_.run();
}

void ServerTCP::handleConnections()
{
    auto Hco =
            [this](boost::system::error_code ec) {
                if (!ec) {
                    ++i;
                    std::cout << "New Connection (ID: " + std::to_string(i) + ")" << std::endl;
                    std::shared_ptr<InstanceClientTCP> newClient = std::make_shared<InstanceClientTCP>(std::move(socket_));
                    newClient->start();
                    newClient->connectionId = i;
                    ServerTCP::Clients.push_back(newClient);
                }
                handleConnections();
            };

    acceptor_.async_accept(socket_, Hco);
}
