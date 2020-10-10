/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#ifndef BABEL_SERVERTCP_HPP
#define BABEL_SERVERTCP_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include "InstanceClientTCP.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <string>
#include <iostream>
#include <deque>
#include <thread>

using boost::asio::ip::tcp;
using boost::asio::ip::address;

class ServerTCP {
public:
    ServerTCP(std::string& ip, int port);
    bool isDisconnectedClients();
    void sendMessageToAllClientsConnected(std::string msg);
    bool newMessageReceived();
    std::string getNewMessageReceivedClientId();
    int getIdClientLastMsg() {return clientIdLastMessage_;}
    std::vector<int> getDisconnectedClientsIds();

    void sendMessageToClient(int id, std::string msg);
    std::string getIpId(int id) {
        for (auto & c : clients_)
            if (c->getId() == id)
                return c->getIp();
        return "";
    }

private:
    void handleConnections();

    std::deque<std::shared_ptr<InstanceClientTCP>> clients_;
    boost::asio::io_service io_service_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;

    std::thread *thread_ = nullptr;
    int idCounter_ = 0;
    std::vector<int> disconnectedClientsId_;

    int clientIdLastMessage_ = -1;
};


#endif //BABEL_SERVERTCP_HPP
