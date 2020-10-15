/*!
 * @file InstanceClientTCP.hpp
 * @brief InstanceClientTCP class prototype
 * @author Cyprien.R
 * @version 1.0
 * @date 10/10/2020
 *
 * Each instance of this class is one client connected to server.
 * Thanks to this class we can connect with each client individually.
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

#include "Communication.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "IInstanceClientTCP.hpp"

using boost::asio::ip::tcp;

class InstanceClientTCP : public std::enable_shared_from_this<InstanceClientTCP>, IInstanceClientTCP {
public:
    InstanceClientTCP(tcp::socket socket, int id);
    ~InstanceClientTCP() = default;

    void startAsyncRead() override;
    void write(std::string&) override;
    std::string getData() const override {return std::string(data_, dataLength_);}
    std::string getDataClear() override {
        std::string tmp = getData();
        clearReceivedData();
        return tmp;
    }
    void clearReceivedData() override {memset(data_, 0, max_length); dataLength_ = 0;}
    int getId() const override {return id_;}
    bool isDisconnected() const override {return disconnected_;}
    std::string getIp() const override {return ip_;}

private:
    int id_;
    tcp::socket socket_;
    enum {
        max_length = 1024
    };
    char data_[max_length]{};
    size_t dataLength_ = 0;
    bool disconnected_ = false;
    std::string ip_;
};

#endif //BABEL_INSTANCECLIENTTCP_HPP
