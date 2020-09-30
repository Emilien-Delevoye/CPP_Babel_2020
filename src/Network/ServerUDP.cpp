/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Network/ServerUDP.hpp"

ServerUDP::ServerUDP(const std::string &IpAddr, int port) : IServerUDP(IpAddr, port) {}

void ServerUDP::openServer()
{
    this->socket.open(udp::v4());
    this->recv_buffer.resize(200);
    this->socket.bind(udp::endpoint(address::from_string("127.0.0.1"), this->_port));
    socket.async_receive_from(boost::asio::buffer(this->recv_buffer), this->remote_endpoint,
        boost::bind(&ServerUDP::handleReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    this->io_service.run();
}

void ServerUDP::handleReceive(const boost::system::error_code &error, size_t bytes_transferred)
{
    std::cout << bytes_transferred << " | " << this->recv_buffer.size() << std::endl;
    if (error) {
        std::cout << "Receive failed: " << error.message() << "\n";
        return;
    }
    std::cout << "Received: '" << this->recv_buffer.data() << "' (" << error.message() << ")\n";
    socket.async_receive_from(boost::asio::buffer(this->recv_buffer), this->remote_endpoint,
        boost::bind(&ServerUDP::handleReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

std::vector<unsigned char> ServerUDP::getFromUDP()
{
    return this->recv_buffer;
}