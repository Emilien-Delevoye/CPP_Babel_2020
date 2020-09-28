/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_CALL_HPP
#define BABEL_CALL_HPP

#include <string>
#include "Network/myUDP.hpp"

class Call {
public:
    explicit Call(const std::string &IpAddress, int port, bool first);
    void setMicState(bool state);
    void setSoundState(bool state);
private:
    bool _micState;
    bool _soundState;
};

#endif //BABEL_CALL_HPP
