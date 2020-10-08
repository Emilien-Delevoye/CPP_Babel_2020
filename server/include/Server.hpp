/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/


#ifndef BABEL_SERVER_HPP
#define BABEL_SERVER_HPP

#include "Communication.hpp"
#include "ServerTCP.hpp"
#include "Users.hpp"

class Server {
public:
    Server(std::string& ip, short port);
    [[noreturn]] void run();

private:
    ServerTCP serverTCP_;
    Communication com_ = Communication(Communication::PRESENTATION);
    DataBase db_;
};


#endif //BABEL_SERVER_HPP
