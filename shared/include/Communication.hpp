/*!
 * @file Communication.hpp
 * @brief Communication class prototype
 * @author Cyprien.R
* @version 1.0
 * @date 10/10/2020
 *
 * This class is used to communicate client to client / server to client / client to server.
 * The variables inside this class are serialized with boost serialization to be able to send the class in TCP communication
*/

#ifndef BABEL_COMMUNICATION_HPP
#define BABEL_COMMUNICATION_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include "BabelException.hpp"

#include <string>
#include <utility>
#include <vector>
#include <boost/asio/buffer.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/text_woarchive.hpp>
#include <boost/archive/text_wiarchive.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/serialization/vector.hpp>
#include <iostream>
#include <sstream>

#define EP std::cerr << "\033[31;1mError: \033[0m" <<
#define EL << std::endl

class Communication {
public:
    enum type {
        PRESENTATION,
        CALL,
        HANG_UP,
        PICK_UP,
        SETUP,
        DISCONNECTED_USER
    };
    explicit Communication(Communication::type t) : t_(t) {}
    Communication(const Communication::type t, const int id) : t_(t), id_(id) {}
    Communication(const Communication::type t, const int myId, const int id, int port) : t_(t), myId_(myId), id_(id), port_(port) {}
    Communication(const Communication::type t, std::string  login, std::string password, const int port) : t_(t), login_(std::move(login)), password_(std::move(password)), port_(port) {}

    type t_;
    int myId_ = -1;
    bool connectionAccepted = false;

    int id_ = -1;
    std::string login_;
    std::string password_;
    std::string ip_;
    int port_ = 4242;

    std::vector<int> ids_;
    std::vector<std::string> logins_;
    std::vector<std::string> ips_;
    std::vector<int> ports_;

    static std::string serializeObj(const Communication obj) {
        std::ostringstream ss;
        boost::archive::text_oarchive oa(ss);
        oa & obj;

        return ss.str();
    }
    std::string serialize() const {
        std::ostringstream ss;
        boost::archive::text_oarchive oa(ss);
        oa & *this;

        return ss.str();
    }
    static Communication unSerializeObj(const std::string obj) {
        Communication c(Communication::PRESENTATION);
        std::istringstream ss(obj);
        boost::archive::text_iarchive ia(ss);
        ia & c;

        return c;
    }
public:
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & t_;

        ar & myId_;
        ar & connectionAccepted;

        ar & id_;
        ar & login_;
        ar & password_;
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
