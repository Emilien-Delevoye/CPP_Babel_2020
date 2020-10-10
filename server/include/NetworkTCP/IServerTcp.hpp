/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/


#ifndef BABEL_ISERVERTCP_HPP
#define BABEL_ISERVERTCP_HPP

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <string>
#include <iostream>
#include <deque>
#include <thread>

using boost::asio::ip::tcp;
using boost::asio::ip::address;

class IServerTCP {
public:
    IServerTCP(std::string& ip, int port) : ip_(ip), port_(port) {};
    virtual bool isDisconnectedClients() = 0;
    virtual void sendMessageToAllClientsConnected(std::string msg) = 0;
    virtual bool newMessageReceived() const = 0;
    virtual std::string getNewMessageReceivedClientId() = 0;
    virtual int getIdClientLastMsg() const = 0;
    virtual std::vector<int> getDisconnectedClientsIds() = 0;

    virtual void sendMessageToClient(int id, std::string msg) = 0;
    virtual std::string getIpId(int id) const = 0;

protected:
    std::string &ip_;
    int port_;

};


#endif //BABEL_ISERVERTCP_HPP
