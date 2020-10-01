/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Network/ServerUDP.hpp"
#include <thread>

ServerUDP::ServerUDP(const std::string &IpAddr, int port) : IServerUDP(IpAddr, port) {}

void ServerUDP::openServer()
{
    this->socket.open(udp::v4());
    this->recv_buffer.resize(200);
    this->socket.bind(udp::endpoint(address::from_string("127.0.0.1"), this->_port));
    socket.async_receive_from(boost::asio::buffer(this->recv_buffer), this->remote_endpoint,
        boost::bind(&ServerUDP::handleReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    this->q = new std::thread([&] { this->io_service.run(); } );
    std::cout << "Server launched" << std::endl;
}

void ServerUDP::handleReceive(const boost::system::error_code &error, size_t bytes_transferred)
{
    this->encBytesFromUDP = bytes_transferred;
    if (error) {
        std::cout << "Receive failed: " << error.message() << "\n";
        return;
    }
    socket.async_receive_from(boost::asio::buffer(this->recv_buffer), this->remote_endpoint,
        boost::bind(&ServerUDP::handleReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

std::vector<unsigned char> ServerUDP::getFromUDP()
{
    return this->recv_buffer;
}

size_t ServerUDP::getEncBytesFromUDP()
{
    return this->encBytesFromUDP;
}
