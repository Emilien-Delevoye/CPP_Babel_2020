/*!
 * @file ServerTCP.cpp
 * @brief boost asio TCP communication server part encapsulation
 * @author Cyprien.R
* @version 1.0
 * @date 10/10/2020
*/

#include "ServerTCP.hpp"

/*!
 * \brief ServerTCP constructor
 * \param server ip (Ip should be set 0.0.0.0 to open server over the internet)
 * \param server port
 *
 * Construct the class that encapsulate TCP communications (server side).
*/

ServerTCP::ServerTCP(std::string& ip, int port) : IServerTCP(ip, port),
        acceptor_(io_service_, tcp::endpoint(address::from_string(ip), port)), socket_(io_service_)
{
    if ((port < 1024) || (port > 60000))
        throw ServerError("Invalid Port", "Port have to be in range 1024-60000");
    handleConnections();

    thread_ = new std::thread([&] { io_service_.run(); });
    std::cout << "Server launched" << std::endl;
}

/*!
 * \brief handleConnections method
 *
 * This method handle new connections and save new clients to communicate with them.
*/

void ServerTCP::handleConnections()
{
    auto Hco =
    [this](boost::system::error_code ec) {
        if (!ec) {
            ++idCounter_;
            std::cout << "\033[32;1mNew Connection\033[0m (ID: " + std::to_string(idCounter_) + ")" << std::endl;
            std::shared_ptr<InstanceClientTCP> newClient = std::make_shared<InstanceClientTCP>(
                    std::move(socket_), idCounter_);
            newClient->startAsyncRead();
            ServerTCP::clients_.push_back(newClient);
        }
        handleConnections();
    };
    acceptor_.async_accept(socket_, Hco);
}

/*!
 * \brief isDisconnectedClients method
 *
 * This method check if there is new disconnected clients
 * This method remove new disconnected clients
*/

bool ServerTCP::isDisconnectedClients()
{
    auto rv = std::any_of(clients_.begin(), clients_.end(), [](const std::shared_ptr<InstanceClientTCP> &o) {return o->isDisconnected();});

    for (auto & client : clients_)
        if (client->isDisconnected())
            disconnectedClientsId_.push_back(client->getId());

    if (rv)
        clients_.erase(std::remove_if(clients_.begin(), clients_.end(),
                   [](const std::shared_ptr<InstanceClientTCP>& o) {return o->isDisconnected();}),
                   clients_.end());
    return rv;
}

/*!
 * \brief getDisconnectedClientsIds method
 *
 * This method return new disconnected clients ids
*/

std::vector<int> ServerTCP::getDisconnectedClientsIds()
{
    auto tmp = disconnectedClientsId_;

    disconnectedClientsId_.clear();
    return tmp;
}

/*!
 * \brief sendMessageToAllClientsConnected method
 * \param msg (msg to send to all clients)
 *
 * This method send the message contained in msg to all connected clients
*/

void ServerTCP::sendMessageToAllClientsConnected(std::string msg) const
{
    for (auto &c : clients_) {
        std::cout << "\033[30;2mSend message to\033[0m " << c->getId() << std::endl;
        c->write(msg);
    }
}

/*!
 * \brief newMessageReceived method
 *
 * This method returns true if a new Message received by any client.
*/

bool ServerTCP::newMessageReceived() const
{
    return std::any_of(clients_.begin(), clients_.end(), [](const std::shared_ptr<InstanceClientTCP> &o) {return !o->getData().empty();});;
}

/*!
 * \brief getNewMessageReceived method
 *
 * This method returns last message received
*/

std::string ServerTCP::getNewMessageReceived()
{
    for (auto &c : clients_)
        if (!c->getData().empty()) {
            clientIdLastMessage_ = c->getId();
            return c->getDataClear();
        }
    std::cerr << "Error in message recuperation" << std::endl;
    return std::string("");
}

/*!
 * \brief getNewMessageReceived method
 * \param int id
 * \param string message
 *
 * This method send the message contained in "msg" to the client having the instance id "id"
*/

void ServerTCP::sendMessageToClient(int id, std::string msg) const
{
    for (auto &c : clients_)
        if (c->getId() == id)
            c->write(msg);
}