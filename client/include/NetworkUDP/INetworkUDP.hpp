/*!
 * @file INetworkUDP.hpp
 * @brief INetworkUDP class prototype
 * @authors Emilien.D
 * @version 1.0
 * @date 15/10/2020
 * ISenderUDP -> Interface for SenderUDP class<br>
 * IReceiverUDP -> Interface for ReceiverUDP class
*/

#ifndef BABEL_INETWORKUDP_HPP
#define BABEL_INETWORKUDP_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include "Audio/Audio.hpp"
#include <string>
#include <vector>
#include <boost/asio/buffer.hpp>

class ISenderUDP {
public:
    explicit ISenderUDP(const std::string &ipAddr, int port) {
        this->_ipAddress = ipAddr;
        this->_port = port;
    }
    virtual void sendToServer(std::vector<unsigned char> in, size_t frameSize) = 0;
protected:
    std::string _ipAddress;
    int _port;
};

class IReceiverUDP {
public:
    explicit IReceiverUDP(int port, Audio *audio) {
        this->_port = port;
        this->_audio = audio;
    }
    virtual void openServer() = 0;
protected:
    int _port;
    Audio *_audio;
};

#endif //BABEL_INETWORKUDP_HPP
