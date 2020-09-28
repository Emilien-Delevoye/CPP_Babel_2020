/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Call.hpp"

Call::Call(const std::string &IpAddressIn, int port, bool first)
{

}

void Call::setMicState(bool state)
{
    this->_micState = state;
}

void Call::setSoundState(bool state)
{
    this->_soundState = state;
}