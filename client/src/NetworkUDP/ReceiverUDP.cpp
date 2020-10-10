/*!
 * @file NetworkUDP/ReceiverUDP.cpp
 * @brief ReceiverUDP class
 * @author Emilien.D
 * @version 1.0
 * @date 10/10/2020
 *
 * Methods implementation for the ReceiverUDP class
*/

#include "ReceiverUDP.hpp"
#include <thread>

/*!
* \brief Constructor for Receiver UDP
* \param IpAddr -> The remote_endpoint Ip Address
* \param port -> The remote_endpoint port
* \param audio -> A pointer to the Audio class
*/

ReceiverUDP::ReceiverUDP(int port, Audio *audio) : IReceiverUDP(port, audio) {}

/*!
* \brief This functions starts the UDP server
*/

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

/*!
* \brief This function stops the server, closes the socket, and waits for the thread
*/

void ReceiverUDP::stopReceiver()
{
    std::cout << "stop io service" << std::endl;
    this->io_service.stop();
    std::cout << "socket close" << std::endl;
    this->socket.close();
    std::cout << "join thread//" << std::endl;
    this->q->join();
    std::cout << "Thread arrêté" << std::endl;
}
