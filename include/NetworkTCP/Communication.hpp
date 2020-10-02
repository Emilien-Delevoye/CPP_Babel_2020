/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#ifndef BABEL_COMMUNICATION_HPP
#define BABEL_COMMUNICATION_HPP

#ifdef _WIN32
#define _WIN32_WINNT  0x0601
#endif

#include <string>
#include <vector>
#include <boost/asio/buffer.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Communication {
public:
    enum type {
        CALL,
        HANG_UP,
        PICK_UP
    };
    Communication(Communication::type t, std::string & ip, std::string & port) : t_(t), ip_(ip), port_(port) {}

    type t_;
    std::string ip_;
    std::string port_;
private:
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & t_;
        ar & ip_;
        ar & port_;
    }
};

#endif //BABEL_COMMUNICATION_HPP
