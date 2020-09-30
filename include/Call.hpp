/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_CALL_HPP
#define BABEL_CALL_HPP

#define _WIN32_WINNT  0x0601

#include "Audio/Audio.hpp"
#include "Network/NetworkUDP.hpp"

class Call : public Audio, public NetworkUDP
{
public:
    explicit Call(const std::string &IpAddress, int port, bool first);
    void setMicState(bool state);
    void setSoundState(bool state);
private:
    bool _micState;
    bool _soundState;
};

#endif //BABEL_CALL_HPP
