/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#include "Server.hpp"

//TODO vérifier que 2 clients ne se log pas avec le même login en même temps
//TODO correctement gérer les ports
//TODO gérer les clients offline
//TODO Quand on est sur un client et qu'il se déconnecte il faut retirer la possibilité de le call

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
                        Communication(Communication::DISCONNECTED_USER, idLInkInstanceDb_[c]).serialize());
        }
        if (serverTCP_.newMessageReceived()) {
            auto msg = Communication::unSerializeObj(serverTCP_.getNewMessageReceivedClientId());
            if (msg.t_ == Communication::PRESENTATION)
                manageNewClients(msg);
            if (msg.t_ == Communication::CALL) {
                printf("%d is calling %d :\n", msg.myId_, msg.id_);
                std::cout << idLInkDbInstance_[msg.id_] << std::endl;
                serverTCP_.sendMessageToClient(idLInkDbInstance_[msg.id_],
                    Communication(Communication::CALL, msg.myId_).serialize());
            }
            if (msg.t_ == Communication::PICK_UP) {
                int idWhoCallDb = idLInkInstanceDb_[serverTCP_.getIdClientLastMsg()];
                serverTCP_.sendMessageToClient(idLInkDbInstance_[msg.id_],
                    Communication(Communication::PICK_UP, idWhoCallDb).serialize());
            }
            if (msg.t_ == Communication::HANG_UP) {
                int idWhoCallDb = idLInkInstanceDb_[serverTCP_.getIdClientLastMsg()];
                serverTCP_.sendMessageToClient(idLInkDbInstance_[msg.id_],
                    Communication(Communication::HANG_UP, idWhoCallDb).serialize());
            }
        }
    }
}

void Server::manageNewClients(const Communication &msg)
{
    auto setup = Communication(Communication::SETUP);

    if (db_.getPasswordFromLogin(msg.login_).empty() or db_.getPasswordFromLogin(msg.login_) == msg.password_) {
        auto login = msg.login_;
        auto password = msg.password_;
        auto ip = serverTCP_.getIpId(serverTCP_.getIdClientLastMsg());
        std::cout << ip << std::endl;
        auto port = msg.port_;

        db_.removeRowFromLogin(msg.login_);
        int idDb = db_.addRow(login, password, ip, port);
        int idInstance = serverTCP_.getIdClientLastMsg();

        idLInkDbInstance_[idDb] = idInstance;
        idLInkInstanceDb_[idInstance] = idDb;

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
