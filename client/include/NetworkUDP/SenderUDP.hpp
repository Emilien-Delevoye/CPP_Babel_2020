/*!
 * @file Call.hpp
 * @brief Call class prototype
 * @authors Emilien.D
 * @version 1.0
 * @date 15/10/2020
 * SenderUDP is the implementation of ISenderUDP
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
    ~SenderUDP();
private:
    udp::socket *_socket = nullptr;
    udp::endpoint *_remote_endpoint = nullptr;
    boost::asio::io_service _io_service;
};

#endif //BABEL_SENDERUDP_HPP
