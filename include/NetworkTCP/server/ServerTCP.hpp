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

#include "NetworkTCP/server/InstanceClientTCP.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <string>
#include <iostream>
#include <deque>
#include "NetworkTCP/Communication.hpp"

using boost::asio::ip::tcp;
using boost::asio::ip::address;

class ServerTCP {
public:
    ServerTCP(std::string& ip, short port);
    static std::deque<std::shared_ptr<InstanceClientTCP>> Clients;

private:
    void handleConnections();

    boost::asio::io_service io_service_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;

    std::thread *thread_ = nullptr;
    int idCounter_ = 0;
};


#endif //BABEL_SERVERTCP_HPP
