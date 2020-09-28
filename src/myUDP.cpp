/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "myUDP.hpp"
#include <boost/asio.hpp>
#include <iostream>

void myClientUDP::init(const std::string& IpAddressIn, int portIn)
{
    boost::asio::io_service io_service;
    this->socket = new boost::asio::ip::udp::socket(io_service);
    this->remote_endpoint = new udp::endpoint(address::from_string(IpAddressIn), portIn);
}

void myClientUDP::createSocket()
{
    this->socket->open(udp::v4());
}

void myClientUDP::sendData(std::string in)
{
    boost::system::error_code err;
    auto sent = socket->send_to(boost::asio::buffer(in), *(this->remote_endpoint), 0, err);

    socket->close();
    std::cout << "Sent Payload --- " << sent << "\n";
}

void myServerUDP::init(const std::string &IpAddressIn, int portIn)
{
    socket.open(udp::v4());
    socket.bind(udp::endpoint(address::from_string(IpAddressIn), portIn));

    wait();

    std::cout << "Receiving\n";
    io_service.run();
    std::cout << "Receiver exit\n";
}

void myServerUDP::wait() {
    socket.async_receive_from(boost::asio::buffer(recv_buffer),
        remote_endpoint,
        boost::bind(&myServerUDP::handleReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void myServerUDP::handleReceive(const boost::system::error_code& error, size_t bytes_transferred) {
    if (error) {
        std::cout << "Receive failed: " << error.message() << "\n";
        return;
    }
    std::cout << "Received: '" << std::string(recv_buffer.begin(), recv_buffer.begin()+bytes_transferred) << "' (" << error.message() << ")\n";
}

void myServerUDP::createSocket()
{
}
