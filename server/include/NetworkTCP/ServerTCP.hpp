/*!
 * @file ServerTCP.hpp
 * @brief ServerTCP class prototype
 * @author Cyprien.R
* @version 1.0
 * @date 10/10/2020
 *
 * The ServerTCP class encapsulate the usage of boost asio TCP socket to manage clients
*/

#ifndef BABEL_SERVERTCP_HPP
#define BABEL_SERVERTCP_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include "InstanceClientTCP.hpp"
#include "IServerTcp.hpp"

class ServerTCP : IServerTCP {
public:
    ServerTCP(std::string& ip, int port);

    bool newMessageReceived() const override;
    std::string getNewMessageReceived() override;
    int getIdClientLastMsg() const override {return clientIdLastMessage_;}

    void sendMessageToClient(int id, std::string msg) const override;
    void sendMessageToAllClientsConnected(std::string msg) const override;

    bool isDisconnectedClients() override;
    std::vector<int> getDisconnectedClientsIds() override;

    std::string getIpId(int id) const override {
        for (auto & c : clients_)
            if (c->getId() == id)
                return c->getIp();
        return "";
    }

private:
    void handleConnections();

    std::deque<std::shared_ptr<InstanceClientTCP>> clients_;
    boost::asio::io_service io_service_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;

    std::thread *thread_ = nullptr;
    int idCounter_ = 0;
    std::vector<int> disconnectedClientsId_;

    int clientIdLastMessage_ = -1;
};


#endif //BABEL_SERVERTCP_HPP
