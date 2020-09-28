/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_SERVERUDP_HPP
#define BABEL_SERVERUDP_HPP

#include "INetwork.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <string>
#include <iostream>

using boost::asio::ip::udp;
using boost::asio::ip::address;

class ServerUDP : IServerUDP {
public:
    explicit ServerUDP(const std::string &IpAddr, int port);
    void openServer() override;
private:
    void handleReceive(const boost::system::error_code &error, size_t bytes_transferred);
    boost::asio::io_service io_service;
    udp::socket socket{io_service};
    boost::array<char, 1024> recv_buffer{};
    udp::endpoint remote_endpoint;
};

#endif //BABEL_SERVERUDP_HPP
