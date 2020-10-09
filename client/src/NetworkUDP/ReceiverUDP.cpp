/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "ReceiverUDP.hpp"
#include <thread>

ReceiverUDP::ReceiverUDP(const std::string &IpAddr, int port, Audio *audio) : IReceiverUDP(IpAddr, port, audio) {}

void ReceiverUDP::openServer()
{
    this->socket.open(udp::v4());
    this->recv_buffer.resize(240);
    this->socket.bind(udp::endpoint(address::from_string("0.0.0.0"), this->_port));
    socket.async_receive_from(boost::asio::buffer(this->recv_buffer), this->remote_endpoint,
        boost::bind(&ReceiverUDP::handleReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    this->q = new std::thread([&] { this->io_service.run(); } );
    std::cout << "Server launched" << std::endl;
}

void ReceiverUDP::handleReceive(const boost::system::error_code &error, size_t bytes_transferred)
{
    this->encBytesFromUDP = bytes_transferred;
    if (error) {
        std::cout << "Receive failed: " << error.message() << std::endl;
        return;
    }
    // Receive data
    this->_audio->setToDecode(this->recv_buffer, bytes_transferred);
    try {
        this->_audio->decodeData();
    } catch (EncodeError &e) {
        std::cerr << e.getComponent() << e.what() << std::endl;
    }
    this->_audio->setDecoded(this->_audio->getDecoded());
    try {
        this->_audio->writeStream();
    } catch (AudioIOError &e) {
        std::cerr << e.getComponent() << e.what() << std::endl;
    }
    socket.async_receive_from(boost::asio::buffer(this->recv_buffer), this->remote_endpoint,
        boost::bind(&ReceiverUDP::handleReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

std::vector<unsigned char> ReceiverUDP::getFromUDP()
{
    return this->recv_buffer;
}

size_t ReceiverUDP::getEncBytesFromUDP() const
{
    return this->encBytesFromUDP;
}

void ReceiverUDP::stopReceiver()
{
    std::cout << "Arrêt du thread" << std::endl;
    this->io_service.stop();
    this->socket.close();
    this->q->join();
    std::cout << "Thread arrêté" << std::endl;
}
