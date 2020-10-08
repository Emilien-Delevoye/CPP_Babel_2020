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
    DataBase db_;

    std::map<int, int> idLInkDbInstance_;
    std::map<int, int> idLInkInstanceDb_;

    void manageNewClients(const Communication &msg);
};


#endif //BABEL_SERVER_HPP
