/*!
 * @file NetworkUDP/NetworkUDP.cpp
 * @brief SenderUDP class
 * @author Emilien.D
 * @version 1.0
 * @date 10/10/2020
 *
 * Methods implementation for the NetworkUDP class
*/

#include "NetworkUDP/NetworkUDP.hpp"

/*!
* \brief Constructor for NetworkUDP, it inits the Sender and the Receiver
* \param IpAddr -> The remote_endpoint Ip Address
* \param portReceiver -> The remote_endpoint receiver port
* \param portSender -> The remote_endpoint sender port
* \param audio -> A pointer to the audio class
*/

NetworkUDP::NetworkUDP(const std::string &ipAddr, int PortReceiver, int PortSender, Audio *audio) : SenderUDP(ipAddr, PortSender), ReceiverUDP(PortReceiver, audio)
{
    this->openServer();
}
