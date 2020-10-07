/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#ifndef BABEL_INSTANCECLIENTTCP_HPP
#define BABEL_INSTANCECLIENTTCP_HPP

#ifdef _WIN32
#define _WIN32_WINNT  0x0601
#endif

#include "Communication.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <string>
#include <iostream>

using boost::asio::ip::tcp;
using boost::asio::ip::address;

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class InstanceClientTCP : public std::enable_shared_from_this<InstanceClientTCP> {
public:
    InstanceClientTCP(tcp::socket socket, int id) : socket_(std::move(socket)), id_(id) {clear();}

    void start();
    void write(std::string);
    std::string getData() {return std::string(data_, dataLength_);}
    std::string getDataClear() {
        std::string tmp = getData();
        clear();
        return tmp;
    }
    void clear() {memset(data_, 0, max_length);}
    int getId() {return id_;}
    bool isDisconnected() {return disconnected_;}
private:
    void read();

    int id_;
    tcp::socket socket_;
    enum {
        max_length = 1024
    };
    char data_[max_length]{};
    size_t dataLength_ = 0;
    bool disconnected_ = false;
};

#endif //BABEL_INSTANCECLIENTTCP_HPP
