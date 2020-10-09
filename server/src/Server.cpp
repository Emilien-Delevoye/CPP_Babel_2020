/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#include "Server.hpp"

//TODO correctement gérer les ports
//TODO Quand on est sur un client et qu'il se déconnecte il faut retirer la possibilité de le call
//TODO vérifier que les clients déconnecté n'ont plus d'id instance et qu'ils ne recoivent pas les messages


Server::Server(std::string &ip, short port) : serverTCP_(ip, port)
{
}

std::ostream& operator<<(std::ostream& os, std::vector<int> v)
{
    for (auto i : v)
        os << i << " ";
    os << std::endl;
    return os;
}

[[noreturn]] void Server::run()
{
    while (true) {
        if (serverTCP_.isDisconnectedClients())
            handleDisconnections();

        if (serverTCP_.newMessageReceived()) {
            auto msg = Communication::unSerializeObj(serverTCP_.getNewMessageReceivedClientId());

            if (msg.t_ == Communication::PRESENTATION)
                manageNewClients(msg);
            else if (msg.t_ == Communication::CALL)
                handleCall(msg);
            else if (msg.t_ == Communication::PICK_UP)
                handlePickUp(msg);
            else if (msg.t_ == Communication::HANG_UP)
                handleHangUp(msg);
        }
    }
}

void Server::handleHangUp(const Communication &msg)
{
    int idWhoCallDb = idLInkInstanceDb_[serverTCP_.getIdClientLastMsg()];
    serverTCP_.sendMessageToClient(idLInkDbInstance_[msg.id_],
                                   Communication(Communication::HANG_UP, idWhoCallDb).serialize());
}

void Server::handlePickUp(const Communication &msg)
{
    int idWhoCallDb = idLInkInstanceDb_[serverTCP_.getIdClientLastMsg()];
    serverTCP_.sendMessageToClient(idLInkDbInstance_[msg.id_],
                                   Communication(Communication::PICK_UP, idWhoCallDb).serialize());
}

void Server::handleCall(const Communication &msg)
{
    printf("%d is calling %d :\n", msg.myId_, msg.id_);
    std::cout << idLInkDbInstance_[msg.id_] << std::endl;
    serverTCP_.sendMessageToClient(idLInkDbInstance_[msg.id_],
                                   Communication(Communication::CALL, msg.myId_).serialize());
}

void Server::handleDisconnections()
{
    auto disconnectedClients = serverTCP_.getDisconnectedClientsIds();
    for (int c : disconnectedClients) {
        if (idLInkInstanceDb_.find(c) == idLInkInstanceDb_.end())
            continue;
        serverTCP_.sendMessageToAllClientsConnected(
                Communication(Communication::DISCONNECTED_USER, idLInkInstanceDb_[c]).serialize());
        idLInkDbInstance_.erase(idLInkInstanceDb_[c]);
        idLInkInstanceDb_.erase(c);
    }
}

void Server::manageNewClients(const Communication &msg)
{
    auto setup = Communication(Communication::SETUP);
    std::cout << "try" << std::endl;
    std::cout << msg.login_ << std::endl;
    std::cout << db_.getPasswordFromLogin(msg.login_) << std::endl;
    std::cout << msg.password_ << std::endl;
    std::cout << (idLInkDbInstance_.find(db_.getIdFromLogin(msg.login_)) == idLInkDbInstance_.end()) << std::endl;

    if (db_.getPasswordFromLogin(msg.login_).empty() or (db_.getPasswordFromLogin(msg.login_) == msg.password_
        and idLInkDbInstance_.find(db_.getIdFromLogin(msg.login_)) == idLInkDbInstance_.end())) {
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

        printf("yes\n");
        for (int i = 0; i < setup.ids_.size(); ++i) {
            if (idLInkDbInstance_.find(setup.ids_.at(i)) == idLInkDbInstance_.end()) {
                std::cout << setup.ids_ << std::endl;
                setup.ids_.erase(setup.ids_.begin() + i);
                setup.logins_.erase(setup.logins_.begin() + i);
                setup.ips_.erase(setup.ips_.begin() + i);
                setup.ports_.erase(setup.ports_.begin() + i);
                std::cout << setup.ids_ << std::endl;
                --i;
            }
        }
        printf("yes end\n");

        printf("CONNECTION ACCEPTED\n");
        serverTCP_.sendMessageToAllClientsConnected(Communication::serializeObj(setup));

    } else {
        int idInstance = serverTCP_.getIdClientLastMsg();
        printf("CONNECTION REFUSED %d\n", idInstance);
        setup.connectionAccepted = false;
        serverTCP_.sendMessageToClient(idInstance, setup.serialize());
    }
}
