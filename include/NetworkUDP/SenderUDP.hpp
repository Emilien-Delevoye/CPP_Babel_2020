/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_SENDERUDP_HPP
#define BABEL_SENDERUDP_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include "INetworkUDP.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <string>
#include <iostream>

using boost::asio::ip::udp;
using boost::asio::ip::address;

class SenderUDP : ISenderUDP {
public:
    explicit SenderUDP(const std::string &IpAddr, int port);
    void sendToServer(std::vector<unsigned char> in, size_t frameSize) override;
private:
    udp::socket *socket = nullptr;
    udp::endpoint *remote_endpoint = nullptr;
};

#endif //BABEL_SENDERUDP_HPP
