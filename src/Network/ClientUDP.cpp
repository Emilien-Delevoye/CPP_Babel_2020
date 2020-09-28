/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include <Network/ClientUDP.hpp>

ClientUDP::ClientUDP(const std::string &IpAddr, int port) : IClientUDP(IpAddr, port) {}

void ClientUDP::connectToServer()
{
    boost::asio::io_service io_service;
    this->socket = new boost::asio::ip::udp::socket(io_service);
    this->remote_endpoint = new udp::endpoint(address::from_string(this->_ipAddress), this->_port);
    this->socket->open(udp::v4());
}

void ClientUDP::sendToServer(std::string in)
{
    boost::asio::io_service io_service;
    udp::socket sck(io_service);
    udp::endpoint remoteEndpoint = udp::endpoint(address::from_string(this->_ipAddress), this->_port);
    sck.open(udp::v4());

    boost::system::error_code err;
    auto sent = sck.send_to(boost::asio::buffer(in), remoteEndpoint, 0, err);
    sck.close();
    std::cout << "Sent Payload --- " << sent << "\n";
}

void ClientUDP::close()
{
    this->socket->close();
}
