/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_RECEIVERUDP_HPP
#define BABEL_RECEIVERUDP_HPP

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

class ReceiverUDP : IReceiverUDP {
public:
    explicit ReceiverUDP(int port, Audio *audio);
    void openServer() override;
    void stopReceiver();
private:
    boost::asio::io_service io_service;
    void handleReceive(const boost::system::error_code &error, size_t bytes_transferred);
    udp::socket socket{io_service};
    std::vector<unsigned char> recv_buffer;
    udp::endpoint remote_endpoint;
    std::thread *q = nullptr;
};

#endif //BABEL_RECEIVERUDP_HPP
