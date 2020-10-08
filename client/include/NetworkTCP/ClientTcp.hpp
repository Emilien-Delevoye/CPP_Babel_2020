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
#include "Communication.hpp"

using boost::asio::ip::tcp;

class ClientTCP {
public:
    ClientTCP(std::string& ip, std::string& port);
    ClientTCP() : resolver(io_context_) {}
    void connect(std::string& ip, std::string& port);
    std::string read();
    void async_read();
    void write(std::string msg);
    void async_write(std::string);

    std::string getData() {return std::string(buffer_, dataLength_);}
    std::string getDataClear() {
        std::string tmp = getData();
        clear();
        return tmp;
    }
    void clear() {
        memset(buffer_, 0, max_length);
        isData = false;
    }

private:
    enum {
        max_length = 1024
    };
    char buffer_[max_length]{};
    std::string data;
    boost::asio::io_context io_context_;
    tcp::socket socket_{io_context_};
    tcp::resolver resolver;
    std::thread *thread_ = nullptr;
    size_t dataLength_ = 0;
    bool isData = false;
};

#endif //BABEL_CLIENTTCP_HPP