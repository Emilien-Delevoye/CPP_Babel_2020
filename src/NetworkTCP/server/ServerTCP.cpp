/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#include "NetworkTCP/server/ServerTCP.hpp"
#include "NetworkTCP/server/CallBacks.hpp"
#include <thread>

ServerTCP::ServerTCP(std::string &ip, short port) :
        acceptor_(io_service_, tcp::endpoint(address::from_string(ip), port)), socket_(io_service_)
{
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
            newClientConnected_ = true;
        }
        handleConnections();
    };
    acceptor_.async_accept(socket_, Hco);
}

bool ServerTCP::newClientConnected()
{
    if (!newClientConnected_)
        return false;
    newClientConnected_ = false;
    return true;
}

bool ServerTCP::newClientDisconnected()
{
    auto rv = std::any_of(clients_.begin(), clients_.end(), [](const std::shared_ptr<InstanceClientTCP> &o) {return o->isDisconnected();});

    if (rv)
        clients_.erase(std::remove_if(clients_.begin(), clients_.end(),
                   [](const std::shared_ptr<InstanceClientTCP>& o) {return o->isDisconnected();}),
                   clients_.end());
    return rv;
}

void ServerTCP::sendMessageToAllClientsConnected(std::string &msg)
{
    for (auto &c : clients_) {
        printf("id %d\n", c->getId());
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
        if (!c->getData().empty())
            return c->getDataClear();
    printf("omg\n");
    return std::string("");
}

void ServerTCP::sendMessageToClient(int id, std::string &msg)
{
    for (auto &c : clients_)
        if (c->getId() == id)
            c->write(msg);
}

