/*!
 * @file Audio/Call.cpp
 * @brief Call class
 * @author Emilien.D
 * @version 1.0
 * @date 10/10/2020
 *
 * Methods implementation for the NetworkUDP class
*/

#include "Call.hpp"

/*!
* \brief Constructor for Call, it inits the Audio and the Network
* \param IpAddr -> The remote_endpoint Ip Address
* \param portReceiver -> The remote_endpoint receiver port
* \param portSender -> The remote_endpoint sender port
*/

Call::Call(const std::string &IpAddressIn, int PortReceiver, int PortSender) : _audio(), _networkUDP(IpAddressIn, PortReceiver, PortSender, &_audio) {}

/*!
* \brief This function runs the audio and the server parts
*/

void Call::run()
{
    while (this->_callActive) {
        try {
            // Send Data
            try {
                this->_audio.readStream();
            } catch (AudioIOError &e) {
                std::cerr << e.getComponent() << e.what() << std::endl;
                continue;
            }
            this->_audio.setCaptured(this->_audio.getCaptured());
            try {
                this->_audio.encodeData();
            } catch (EncodeError &e) {
                std::cerr << e.getComponent() << e.what() << std::endl;
                continue;
            }
            this->_networkUDP.sendToServer(this->_audio.getEncoded(), this->_audio.getEncBytes());
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

/*!
* \brief This function stops the call (Sender and Receiver)
*/

void Call::stopCall()
{
    this->_callActive = false;
    this->_networkUDP.stopReceiver();
}