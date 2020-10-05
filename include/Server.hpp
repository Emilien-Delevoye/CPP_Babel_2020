/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/


#ifndef BABEL_SERVER_HPP
#define BABEL_SERVER_HPP

#include "NetworkTCP/Communication.hpp"
#include "NetworkTCP/server/ServerTCP.hpp"

class Server {
public:
    [[noreturn]] Server(std::string& ip, short port);

private:
    ServerTCP serverTCP_;

};


#endif //BABEL_SERVER_HPP
