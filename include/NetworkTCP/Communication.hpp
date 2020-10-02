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
        PRESENTATION,
        CALL,
        HANG_UP,
        PICK_UP,
        UPDATE_CLIENTS
    };
    Communication(Communication::type t, std::string & ip, std::string & port) : t_(t), ip_(ip), port_(port) {}

    type t_;

    // Call / Presentation
    int id_;
    std::string name_;
    std::string ip_;
    std::string port_;

    // Update clients
    std::vector<int> ids_;
    std::vector<std::string> names_;
    std::vector<std::string> ips_;
    std::vector<std::string> ports_;
private:
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & id_;
        ar & t_;
        ar & ip_;
        ar & port_;

        ar & ids_;
        ar & names_;
        ar & ips_;
        ar & ports_;
    }
};

#endif //BABEL_COMMUNICATION_HPP
