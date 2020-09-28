/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_MYUDP_HPP
#define BABEL_MYUDP_HPP

#include "INetwork.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <string>

using boost::asio::ip::udp;
using boost::asio::ip::address;

class myClientUDP : IClientUDP {
public:
    void init(const std::string& IpAddressIn, int portIn) override;
    void createSocket() override;
    void sendData(std::string) override;
private:
    boost::asio::ip::udp::socket *socket = nullptr;
    boost::asio::ip::udp::endpoint *remote_endpoint = nullptr;
};

class myServerUDP : IServerUDP {
public:
    void init(const std::string& IpAddressIn, int portIn) override;
    void createSocket() override;
protected:
    void handleReceive(const boost::system::error_code &error, size_t bytes_transferred);
private:
    void wait();
    boost::asio::io_service io_service;
    udp::socket socket{io_service};
    boost::array<char, 1024> recv_buffer;
    udp::endpoint remote_endpoint;
};

#endif //BABEL_MYUDP_HPP
