/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#ifndef BABEL_INSTANCECLIENTTCP_HPP
#define BABEL_INSTANCECLIENTTCP_HPP

#ifdef _WIN32
#define _WIN32_WINNT  0x0601
#endif

#include "NetworkTCP/Communication.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <string>
#include <iostream>

using boost::asio::ip::tcp;
using boost::asio::ip::address;

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class InstanceClientTCP : public std::enable_shared_from_this<InstanceClientTCP> {
public:
    InstanceClientTCP(tcp::socket socket) : socket_(std::move(socket)) {}

    void start();

    int id_;
private:
    void read();
    void write(std::string);

    tcp::socket socket_;
    enum {
        max_length = 1024
    };
    char data_[max_length];
};

#endif //BABEL_INSTANCECLIENTTCP_HPP
