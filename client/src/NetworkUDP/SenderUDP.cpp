/*!
 * @file NetworkUDP/SenderUDP.cpp
 * @brief SenderUDP class
 * @author Emilien.D
 * @version 1.0
 * @date 10/10/2020
 *
 * Methods implementation for the SenderUDP class
*/

#include "NetworkUDP/SenderUDP.hpp"

/*!
* \brief Constructor for SenderUDP, it inits the socket and connect it to the remote_endpoint
* \param IpAddr -> The remote_endpoint Ip Address
* \param port -> The remote_endpoint port
*/

SenderUDP::SenderUDP(const std::string &IpAddr, int port) : ISenderUDP(IpAddr, port)
{
    this->_socket = new udp::socket(this->_io_service);
    this->_socket->open(udp::v4());
    this->_remote_endpoint = new udp::endpoint(address::from_string(this->_ipAddress), this->_port);
    this->_socket->connect((*this->_remote_endpoint));
}

/*!
* \brief This function sends a vector to the remote endpoint
* \param in -> is the vector to send to the remote endpoint
* \param frameSize -> is the size to send
*/

void SenderUDP::sendToServer(std::vector<unsigned char> in, size_t frameSize)
{
    boost::system::error_code err;
    this->_socket->send(boost::asio::buffer(in, frameSize), 0, err);
    if (err)
        std::cerr << err << std::endl;
}

/*!
* \brief Destructor for AudioIO, it closes the UDP socket
*/

SenderUDP::~SenderUDP()
{
    this->_socket->close();
}