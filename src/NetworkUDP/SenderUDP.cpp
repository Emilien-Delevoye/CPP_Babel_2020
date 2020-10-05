/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Network/SenderUDP.hpp"

SenderUDP::SenderUDP(const std::string &IpAddr, int port) : ISenderUDP(IpAddr, port)
{
    this->_socket = new udp::socket(this->_io_service);
    this->_socket->open(udp::v4());
    this->_remote_endpoint = new udp::endpoint(address::from_string(this->_ipAddress), this->_port);
    this->_socket->connect((*this->_remote_endpoint));
}

void SenderUDP::sendToServer(std::vector<unsigned char> in, size_t frameSize)
{
    boost::system::error_code err;
    this->_socket->send(boost::asio::buffer(in, frameSize), 0, err);
    if (err)
        std::cerr << err << std::endl;
}

SenderUDP::~SenderUDP()
{
    this->_socket->close();
}