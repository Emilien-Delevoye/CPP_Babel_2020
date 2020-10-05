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
            newClientConnected_ = true;
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

bool ServerTCP::newClientConnected()
{
    if (!newClientConnected_)
        return false;
    newClientConnected_ = false;
    return true;
}

bool ServerTCP::newClientDisconnected()
{
    for (int i = 0; i < ServerTCP::clients_.size(); ++i) {
        if (clients_[i]->isDisconnected()) {
            clients_.erase(ServerTCP::clients_.begin() + i);
            return true;
        }
    }
    return true;
}

void ServerTCP::sendMessageToAllClientsConnected(std::string &msg)
{
    for (auto &c : clients_)
        c->write(msg);
}

bool ServerTCP::newMessageReceived()
{
    for (auto &c : clients_)
        if (!c->getData().empty()) {
            messageClientId_ = c->getId();
            return true;
        }
    return false;
}

std::string ServerTCP::getNewMessageReceivedClientId()
{
    for (auto &c : clients_)
        if (c->getId() == messageClientId_ and messageClientId_ != -1)
            return c->getData();
    std::cerr << "\033[31;1mError Empty message\033[0m" << std::endl;
    return std::string("");
}

void ServerTCP::sendMessageToClient(int id, std::string &msg)
{
    for (auto &c : clients_) {
        if (c->getId() == id)
            c->write(msg);
    }
}

