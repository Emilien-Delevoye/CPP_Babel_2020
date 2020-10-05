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
#include "NetworkTCP/Communication.hpp"

using boost::asio::ip::tcp;

class ClientTCP {
public:
    ClientTCP(std::string& ip, std::string& port);
    std::string read();
    void async_read();
    void write(std::string msg);
    void async_write(std::string);
    void setCheckMessageIntegrityCallBack(callBackFct);

private:
    enum {
        max_length = 1024
    };
    char buffer_[max_length];
    std::string data;
    boost::asio::io_context io_context_;
    tcp::socket socket_{io_context_};
    tcp::resolver resolver;
    std::thread *thread_ = nullptr;
    callBackFct cbf_;
    std::string errorMessage;
    std::string validMessage;
};


#endif //BABEL_CLIENTTCP_HPP
