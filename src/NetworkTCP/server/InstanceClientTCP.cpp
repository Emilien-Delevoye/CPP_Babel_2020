/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#include "NetworkTCP/server/InstanceClientTCP.hpp"
#include "NetworkTCP/server/ServerTCP.hpp"

void InstanceClientTCP::start()
{
    read();
}

void InstanceClientTCP::read()
{
    auto self(shared_from_this());
    auto Hrd =
            [this, self](boost::system::error_code ec, std::size_t length) {

                // If the client is disconnected
                if ((boost::asio::error::eof == ec) || (boost::asio::error::connection_reset == ec)) {
                    std::cout << "Disconnected ID: " + std::to_string(connectionId) << std::endl;
                    // Search it in the client list
                    for (int i = 0; i < ServerTCP::Clients.size(); ++i) {
                        if (ServerTCP::Clients[i]->connectionId == connectionId)
                            // Remove him from the list
                            ServerTCP::Clients.erase(ServerTCP::Clients.begin() + i);
                    }
                } else {
                    // If not disconnected, we print the received message
                    std::cout << "\033[31m[Client's message]:\033[0m ";
                    std::cout.write(data_, length);
                    std::cout << "\n";
                    // Answer "Yes"
                    //memset(data_, 0, length);
                    //strcpy(data_, "Automactic answer from server");
                    sleep(1);
                    write(std::string("Automactic answer from server id: ") + std::to_string(this->connectionId));
                }
            };

    socket_.async_read_some(boost::asio::buffer(data_, max_length), Hrd);
}

void InstanceClientTCP::write(std::string msg)
{
    auto self(shared_from_this());
    auto Hwt =
            [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                if (!ec) {
                    read();
                }
            };

    std::cout << "\033[32mSend\033[0m " << msg << std::endl;
    boost::asio::async_write(socket_, boost::asio::buffer(msg, msg.length()), Hwt);
}