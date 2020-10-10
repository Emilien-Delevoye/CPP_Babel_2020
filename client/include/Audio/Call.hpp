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
#include "NetworkUDP/NetworkUDP.hpp"
#include "BabelException.hpp"

class Call
{
public:
    explicit Call(const std::string &IpAddress, int PortReceiver, int PortSender);
    void run();
    void stopCall();
private:
    Audio _audio;
    NetworkUDP _networkUDP;
    bool _micState;
    bool _soundState;
    bool _callActive = true;
};

#endif //BABEL_CALL_HPP
