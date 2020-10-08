/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#include "Server.hpp"

//TODO vérifier que 2 clients ne se log pas avec le même login en même temps

Server::Server(std::string &ip, short port) : serverTCP_(ip, port)
{
}

[[noreturn]] void Server::run()
{
    while (true) {
        if (serverTCP_.isDisconnectedClients()) {
            auto disconnectedClients = serverTCP_.getDisconnectedClientsIds();
            for (int c : disconnectedClients)
                serverTCP_.sendMessageToAllClientsConnected(
                        Communication(Communication::DISCONNECTED_USER, c).serialize());
        }
        if (serverTCP_.newMessageReceived()) {
            auto msg = Communication::unSerializeObj(serverTCP_.getNewMessageReceivedClientId());
            if (msg.t_ == Communication::PRESENTATION)
                manageNewClients(msg);
        }
    }
}

void Server::manageNewClients(const Communication &msg)
{
    auto setup = Communication(Communication::SETUP);

    std::cout << "password " << db_.getPasswordFromLogin(msg.login_) << "__" << msg.password_ << std::endl;
    if (db_.getPasswordFromLogin(msg.login_).empty() or db_.getPasswordFromLogin(msg.login_) == msg.password_) {
        auto login = msg.login_;
        auto password = msg.password_;
        auto ip = serverTCP_.getIpId(serverTCP_.getIdClientLastMsg());
        auto port = msg.port_;

        db_.removeRowFromLogin(msg.login_);
        int idDb = db_.addRow(login, password, ip, port);
        int idInstance = serverTCP_.getIdClientLastMsg();

        idLInkServerInstance_.emplace_back(idDb, idInstance);

        setup.connectionAccepted = true;
        setup.id_ = idDb;

        setup.ids_ = db_.getIds();
        setup.logins_ = db_.getLogins();
        setup.ips_ = db_.getIPs();
        setup.ports_ = db_.getPorts();

        printf("CONNECTION ACCEPTED\n");
        serverTCP_.sendMessageToAllClientsConnected(Communication::serializeObj(setup));

    } else {
        printf("CONNECTION REFUSED\n");
        setup.connectionAccepted = false;
        serverTCP_.sendMessageToAllClientsConnected(setup.serialize());
    }
}
