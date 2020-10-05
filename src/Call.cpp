/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Call.hpp"

Call::Call(const std::string &IpAddressIn, int PortReceiver, int PortSender) : _audio(), _networkUDP(IpAddressIn, PortReceiver, PortSender, &_audio)
{
    while (this->_callActive) {
        try {
            // Send Data
            try {
                this->_audio.readStream();
            } catch (PortaudioError &e) {
                std::cerr << e.getComponent() << e.what() << std::endl;
                continue;
            }
            this->_audio.setCaptured(this->_audio.getCaptured());
            try {
                this->_audio.encodeData();
            } catch (OpusError &e) {
                std::cerr << e.getComponent() << e.what() << std::endl;
                continue;
            }
            this->_networkUDP.sendToServer(this->_audio.getEncoded(), this->_audio.getEncBytes());
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