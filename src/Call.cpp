/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Call.hpp"

extern int status_sound;

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

            // Receive data
            this->_audio.setToDecode(this->_networkUDP.getFromUDP(), this->_networkUDP.getEncBytesFromUDP());
            try {
                this->_audio.decodeData();
            } catch (OpusError &e) {
                std::cerr << e.getComponent() << e.what() << std::endl;
                continue;
            }
            this->_audio.setDecoded(this->_audio.getDecoded());
            try {
                if (status_sound == 1)
                    this->_audio.writeStream();
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