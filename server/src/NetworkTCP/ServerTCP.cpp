/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#include "ServerTCP.hpp"

ServerTCP::ServerTCP(std::string &ip, int port) :
        acceptor_(io_service_, tcp::endpoint(address::from_string(ip), port)), socket_(io_service_)
{
    if ((port < 1024) || (port > 60000))
        throw ServerError("Invalid Port", "Port have to be in range 1024-60000");
    handleConnections();

    thread_ = new std::thread([&] { io_service_.run(); });
    std::cout << "Server launched" << std::endl;
}

void ServerTCP::handleConnections()
{
    auto Hco =
    [this](boost::system::error_code ec) {
        if (!ec) {
            ++idCounter_;
            std::cout << "New Connection (ID: " + std::to_string(idCounter_) + ")" << std::endl;
            std::shared_ptr<InstanceClientTCP> newClient = std::make_shared<InstanceClientTCP>(
                    std::move(socket_), idCounter_);
            newClient->start();
            ServerTCP::clients_.push_back(newClient);
        }
        handleConnections();
    };
    acceptor_.async_accept(socket_, Hco);
}

bool ServerTCP::isDisconnectedClients()
{
    auto rv = std::any_of(clients_.begin(), clients_.end(), [](const std::shared_ptr<InstanceClientTCP> &o) {return o->isDisconnected();});

    for (auto & client : clients_)
        if (client->isDisconnected())
            disconnectedClientsId_.push_back(client->getId());

    if (rv)
        clients_.erase(std::remove_if(clients_.begin(), clients_.end(),
                   [](const std::shared_ptr<InstanceClientTCP>& o) {return o->isDisconnected();}),
                   clients_.end());
    return rv;
}

std::vector<int> ServerTCP::getDisconnectedClientsIds()
{
    auto tmp = disconnectedClientsId_;

    disconnectedClientsId_.clear();
    return tmp;
}

void ServerTCP::sendMessageToAllClientsConnected(std::string msg)
{
    for (auto &c : clients_) {
        std::cout << "send msg to " << c->getId() << std::endl;
        c->write(msg);
    }
}

bool ServerTCP::newMessageReceived()
{
    return std::any_of(clients_.begin(), clients_.end(), [](const std::shared_ptr<InstanceClientTCP> &o) {return !o->getData().empty();});;
}

std::string ServerTCP::getNewMessageReceivedClientId()
{
    for (auto &c : clients_)
        if (!c->getData().empty()) {
            clientIdLastMessage_ = c->getId();
            return c->getDataClear();
        }
    std::cerr << "Error in message recuperation" << std::endl;
    return std::string("");
}

void ServerTCP::sendMessageToClient(int id, std::string msg)
{
    for (auto &c : clients_)
        if (c->getId() == id) {
            c->write(msg);
        }
}