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

#include "NetworkTCP/Communication.hpp"
#include "NetworkTCP/server/InstanceClientTCP.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <string>
#include <iostream>
#include <deque>

using boost::asio::ip::tcp;
using boost::asio::ip::address;

class ServerTCP {
public:
    ServerTCP(short port);
    static std::deque<std::shared_ptr<InstanceClientTCP>> Clients;

private:
    void handleConnections();
    //void handleMessage(void *);
    boost::asio::io_service io_service_;
    int i = 0;
    tcp::acceptor acceptor_;
    tcp::socket socket_;
};


#endif //BABEL_SERVERTCP_HPP
