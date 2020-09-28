/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_CLIENTUDP_HPP
#define BABEL_CLIENTUDP_HPP

#include "INetwork.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <string>

using boost::asio::ip::udp;
using boost::asio::ip::address;

class ClientUDP : IClientUDP {
public:
    explicit ClientUDP(const std::string &IpAddr, int port);
private:
    udp::socket *socket = nullptr;
    udp::endpoint *remote_endpoint = nullptr;
};

#endif //BABEL_CLIENTUDP_HPP
