/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Call.hpp"

Call::Call(const std::string &IpAddressIn, int port, bool first) : Audio(), NetworkUDP(IpAddressIn, port, first)
{
    while (this->_callActive) {
        try {
            // Send Data
            try {
                this->readStream();
            } catch (PortaudioError &e) {
                std::cerr << e.getComponent() << e.what() << std::endl;
                continue;
            }
            this->setCaptured(this->getCaptured());
            try {
                this->encodeData();
            } catch (OpusError &e) {
                std::cerr << e.getComponent() << e.what() << std::endl;
                continue;
            }
            this->sendToServer(this->getEncoded(), this->getEncBytes());

            // Receive data
            this->setToDecode(this->getFromUDP(), this->getEncBytesFromUDP());
            try {
                this->decodeData();
            } catch (OpusError &e) {
                std::cerr << e.getComponent() << e.what() << std::endl;
                continue;
            }
            this->setDecoded(this->getDecoded());
            try {
                this->writeStream();
            } catch (PortaudioError &e) {
                std::cerr << e.getComponent() << e.what() << std::endl;
                continue;
            }
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

void Call::setMicState(bool state)
{
    this->_micState = state;
}

void Call::setSoundState(bool state)
{
    this->_soundState = state;
}

void Call::stopCall()
{
    this->_callActive = false;
}