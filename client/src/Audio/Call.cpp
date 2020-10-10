/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Call.hpp"

Call::Call(const std::string &IpAddressIn, int PortReceiver, int PortSender) : _audio(), _networkUDP(IpAddressIn, PortReceiver, PortSender, &_audio) {}

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

void Call::stopCall()
{
    this->_callActive = false;
    this->_networkUDP.stopReceiver();
}