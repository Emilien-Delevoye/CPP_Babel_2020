/*!
 * @file Server.cpp
 * @brief Server class implementation
 * @author Cyprien R
 * @version 1.0
 * @date 10/10/2020
*/

#include "Server.hpp"

/*!
 * \brief Server constructor
 * \param server ip (Ip should be set 0.0.0.0 to open server over the internet)
 * \param server port
 *
 * Construct the class that manage connections between clients.
*/

Server::Server(std::string ip, int port) : serverTCP_(ip, port) {}

/*!
 * \brief run method
 *
 * This method start and keep the server alive.
 * it constantly check is client send a message to answer him and prevent the others about what's happening.
*/

[[noreturn]] void Server::run()
{
    Communication msg;

    while (true) {
        if (serverTCP_.isDisconnectedClients())
            handleDisconnections();

        if (serverTCP_.newMessageReceived()) {
            try {
                msg = Communication::unSerializeObj(serverTCP_.getNewMessageReceivedClientId());
            } catch (boost::archive::archive_exception &e) {
                EP "Invalid message" EL;
                continue;
            }
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

/*!
 * \brief handleHangUp method
 * \param Communication Class (msg received from client)
 *
 * this method send a HANG UP message to the client who need to receive it. The server know to which client send it
 * because the client which sent the message specified it in the message.
 * It's a bridge between the 2 clients.
*/

void Server::handleHangUp(const Communication &msg)
{
    int idWhoCallDb = idLInkInstanceDb_[serverTCP_.getIdClientLastMsg()];

    serverTCP_.sendMessageToClient(idLInkDbInstance_[msg.id_],
                                   Communication(Communication::HANG_UP, idWhoCallDb).serialize());
}

/*!
 * \brief handlePickUp method
 * \param Communication Class (msg received from client)
 *
 * this method send a PICK UP message to the client who need to receive it. The server know to which client send it
 * because the client which sent the message specified it in the message.
 * It's a bridge between the 2 clients.
*/

void Server::handlePickUp(const Communication &msg)
{
    int idWhoCallDb = idLInkInstanceDb_[serverTCP_.getIdClientLastMsg()];
    serverTCP_.sendMessageToClient(idLInkDbInstance_[msg.id_],
                                   Communication(Communication::PICK_UP, idWhoCallDb).serialize());
}

/*!
 * \brief handleCall method
 * \param Communication Class (msg received from client)
 *
 * this method send a CALL message to the client who need to receive it. The server know to which client send it
 * because the client which sent the message specified it in the message.
 * It's a bridge between the 2 clients.
*/

void Server::handleCall(const Communication &msg)
{
    printf("%d is calling %d\n", msg.myId_, msg.id_);
    serverTCP_.sendMessageToClient(idLInkDbInstance_[msg.id_],
                                   Communication(Communication::CALL, msg.myId_).serialize());
}

/*!
 * \brief handleDisconnections method
 *
 * this method prevents connected clients about disconnected clients.
*/

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

/*!
 * \brief canConnect method
 * \param Communication Class (msg received from client)
 *
 * this method check if a newly connected client has good login and password or if someone else is not already connected
 * with the same logins
*/

bool Server::canConnect(const Communication &msg)
{
    return db_.getPasswordFromLogin(msg.login_).empty() or
           (db_.getPasswordFromLogin(msg.login_) == msg.password_
            and idLInkDbInstance_.find(db_.getIdFromLogin(msg.login_)) == idLInkDbInstance_.end());
}

/*!
 * \brief canConnect method
 * \param Communication Class (msg received from client)
 *
 * this method directs the server to which message it has to send depending on whether the client can connect or not.
*/

void Server::manageNewClients(const Communication &msg)
{
    if (canConnect(msg))
        connectionAccepted(msg);
    else
        connectionRefused();
}

/*!
 * \brief connectionRefused method
 *
 * this method send a message to inform the newly connected client that its connection is refused
*/

void Server::connectionRefused()
{
    auto setup = Communication(Communication::SETUP);
    int idInstance = serverTCP_.getIdClientLastMsg();

    printf("\033[31mCONNECTION REFUSED [ID instance %d]\033[0m\n", idInstance);
    setup.connectionAccepted = false;
    serverTCP_.sendMessageToClient(idInstance, setup.serialize());
}

/*!
 * \brief connectionAccepted method
 * \param Communication Class (msg received from client)
 *
 * this method send a message to inform the newly connected client that its connection is accepted
*/

void Server::connectionAccepted(const Communication &msg)
{
    auto setup = Communication(Communication::SETUP);

    db_.removeRowFromLogin(msg.login_);

    auto login = msg.login_;
    auto password = msg.password_;
    auto ip = serverTCP_.getIpId(serverTCP_.getIdClientLastMsg());
    auto port = msg.port_;
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

    for (int i = 0; i < setup.ids_.size(); ++i) {
        if (!(idLInkDbInstance_.find(setup.ids_.at(i)) == idLInkDbInstance_.end()))
            continue;
        setup.ids_.erase(setup.ids_.begin() + i);
        setup.logins_.erase(setup.logins_.begin() + i);
        setup.ips_.erase(setup.ips_.begin() + i);
        setup.ports_.erase(setup.ports_.begin() + i);
        --i;
    }

    printf("\033[34mCONNECTION ACCEPTED [ID instance %d]\033[0m\n", idInstance);
    serverTCP_.sendMessageToAllClientsConnected(Communication::serializeObj(setup));
}