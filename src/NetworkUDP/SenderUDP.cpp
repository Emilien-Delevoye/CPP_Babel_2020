/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Network/SenderUDP.hpp"

SenderUDP::SenderUDP(const std::string &IpAddr, int port) : ISenderUDP(IpAddr, port) {}

void SenderUDP::sendToServer(std::vector<unsigned char> in, size_t frameSize)
{
    boost::asio::io_service io_service;
    udp::socket sck(io_service);
    udp::endpoint remoteEndpoint = udp::endpoint(address::from_string(this->_ipAddress), this->_port);
    sck.open(udp::v4());

    boost::system::error_code err;
    sck.send_to(boost::asio::buffer(in, frameSize), remoteEndpoint, 0, err);
    sck.close();
}