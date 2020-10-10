/*!
 * @file Server.hpp
 * @brief Server class prototype
 * @author Cyprien R
 * @version 1.0
 * @date 10/10/2020
 *
 * This class represent the whole server.<br>
 * Once you started it with the run function you cannot stop it anymore.
 * This class handle different clients and allow them to communicate.
*/

#ifndef BABEL_SERVER_HPP
#define BABEL_SERVER_HPP

#include "Communication.hpp"
#include "ServerTCP.hpp"
#include "Users.hpp"

class Server {
public:
    Server(std::string ip, int port);
    [[noreturn]] void run();

private:
    ServerTCP serverTCP_;
    DataBase db_;

    std::map<int, int> idLInkDbInstance_;
    std::map<int, int> idLInkInstanceDb_;

    void manageNewClients(const Communication &msg);
    void handleDisconnections();
    void handleCall(const Communication &msg);
    void handlePickUp(const Communication &msg);
    void handleHangUp(const Communication &msg);

    bool canConnect(const Communication &msg);
    void connectionAccepted(const Communication &msg);
    void connectionRefused();
};


#endif //BABEL_SERVER_HPP
