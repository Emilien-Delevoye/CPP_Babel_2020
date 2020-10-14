/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/


#ifndef BABEL_CLIENTTCP_HPP
#define BABEL_CLIENTTCP_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include <boost/asio.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/system/system_error.hpp>
#include <boost/asio/write.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include "Communication.hpp"

using boost::asio::ip::tcp;
using boost::asio::deadline_timer;
using boost::asio::ip::tcp;
using boost::lambda::bind;
using boost::lambda::var;
using boost::lambda::_1;

class ClientTCP {
public:
    ClientTCP(std::string& ip, std::string& port);
    ClientTCP() : resolver(io_context_), deadline_(io_context_) {}
    ~ClientTCP() = default;

    bool connect(std::string& ip, std::string& port);
    std::string read();
    void async_read();
    void write(std::string msg);
    void async_write(std::string);
    void startAsyncRead();
    void disconnectThread();
    void disconnect();

    void connectTimeOut(const std::string& host, const std::string& service, boost::posix_time::time_duration timeout);
    void check_deadline();
    std::string getData() {return std::string(buffer_, dataLength_);}
    std::string getDataClear() {
        std::string tmp = getData();
        clear();
        return tmp;
    }
    void clear() {
        memset(buffer_, 0, max_length);
        dataLength_ = 0;
    }
    bool isDisconnected() const {return justDisconnected_;}
    void isNotJustDisconnected() {justDisconnected_ = false;}
private:
    bool justDisconnected_ = false;
    enum {
        max_length = 2048
    };
    char buffer_[max_length]{};
    std::string data;
    boost::asio::io_context io_context_;
    tcp::socket socket_{io_context_};
    tcp::resolver resolver;
    std::thread *thread_ = nullptr;
    size_t dataLength_ = 0;
    deadline_timer deadline_;
};

#endif //BABEL_CLIENTTCP_HPP