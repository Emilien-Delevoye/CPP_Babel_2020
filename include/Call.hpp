/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_CALL_HPP
#define BABEL_CALL_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include "Audio/Audio.hpp"
#include "Network/NetworkUDP.hpp"
#include "BabelException.hpp"

class Call : public Audio, public NetworkUDP
{
public:
    explicit Call(const std::string &IpAddress, int PortReceiver, int PortSender);
    void setMicState(bool state);
    void setSoundState(bool state);
    void stopCall();
private:
    bool _micState;
    bool _soundState;
    bool _callActive = true;
};

#endif //BABEL_CALL_HPP
