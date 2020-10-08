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
#include <utility>
#include <vector>
#include <boost/asio/buffer.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <iostream>

class Communication {
public:
    enum type {
        PRESENTATION,
        CALL,
        HANG_UP,
        PICK_UP,
        UPDATE_CLIENTS,
        CONFIRMATION,
        INIT,
        NEW_USER,
        DISCONNECTED_USER
    };
    Communication(Communication::type t=INIT) : t_(t) {}
    Communication(Communication::type t, int myId, int id) : t_(t), myId_(myId), id_(id) {}
    Communication(Communication::type t, int id) : t_(t), id_(id) {}
    Communication(Communication::type t, std::string login, std::string password) : t_(t), login_(login), password_(password) {}

    type t_;

    int myId_ = -1;

    // Call / Presentation / New / Disconnected
    int id_ = -1;
    std::string login_;
    std::string password_;
    std::string ip_;
    std::string port_;

    // Update clients
    std::vector<int> ids_;
    std::vector<std::string> logins_;
    std::vector<std::string> ips_;
    std::vector<std::string> ports_;

    static std::string serializeObj(Communication &obj) {
        std::ostringstream ss;
        boost::archive::binary_oarchive oa(ss);
        oa & obj;

        return ss.str();
    }
    static std::string serializeObj(Communication obj) {
        std::ostringstream ss;
        boost::archive::binary_oarchive oa(ss);
        oa & obj;

        return ss.str();
    }
    std::string serialize() const {
        std::ostringstream ss;
        boost::archive::binary_oarchive oa(ss);
        oa & *this;

        return ss.str();
    }
    static Communication unSerializeObj(std::string &obj) {
        Communication c(Communication::PRESENTATION);
        std::istringstream ss(obj);
        boost::archive::binary_iarchive ia(ss);
        ia & c;

        return c;
    }
public:
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & t_;

        ar & id_;
        ar & login_;
        ar & ip_;
        ar & port_;

        ar & ids_;
        ar & logins_;
        ar & ips_;
        ar & ports_;
    }
};
typedef Communication (*callBackFct)(std::string &obj);

#endif //BABEL_COMMUNICATION_HPP
