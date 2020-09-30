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
        this->readStream();
        this->setCaptured(this->getCaptured());
        this->encodeData();
        this->getEncoded();
        this->sendToServer(this->getEncoded(), this->getEncBytes());
        this->setToDecode(this->getFromUDP(), this->getEncBytesFromUDP());
        this->decodeData();
        this->setDecoded(this->getDecoded());
        this->writeStream();
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