/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/


#ifndef BABEL_CLIENTTCP_HPP
#define BABEL_CLIENTTCP_HPP

#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

class ClientTCP {
public:
    ClientTCP(std::string& ip, std::string& port);
    std::string read();
    void async_read();
    void write(std::string msg);
    void async_write(std::string);

private:
    enum {
        max_length = 1024
    };
    char data_[max_length];
    boost::asio::io_context io_context_;
    tcp::socket socket_{io_context_};
    tcp::resolver resolver;
};


#endif //BABEL_CLIENTTCP_HPP
