/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#include "NetworkTCP/server/ServerTCP.hpp"
#include "NetworkTCP/server/CallBacks.hpp"
#include <thread>

// Receive Msg -> client nb & msg
// Receive Msg from client -> msg
// Send Msg to (client, msg)
// Send Msg to all clients (msg)

/* On reçoit les demandes de call / raccrochage / décrochage */

std::deque<std::shared_ptr<InstanceClientTCP>> ServerTCP::Clients;

ServerTCP::ServerTCP(std::string &ip, short port) : acceptor_(io_service_, tcp::endpoint(address::from_string(ip), port)),
                                                    socket_(io_service_)
{
    handleConnections();

    thread_ = new std::thread([&] { io_service_.run(); } );
    std::cout << "Server launched" << std::endl;
}

void ServerTCP::handleConnections()
{
    auto Hco =
    [this](boost::system::error_code ec) {
        if (!ec) {
            ++idCounter_;
            std::cout << "New Connection (ID: " + std::to_string(idCounter_) + ")" << std::endl;
            std::shared_ptr<InstanceClientTCP> newClient = std::make_shared<InstanceClientTCP>(std::move(socket_), idCounter_);
            newClient->start();
            ServerTCP::Clients.push_back(newClient);
        }
        handleConnections();
    };

    acceptor_.async_accept(socket_, Hco);
}
