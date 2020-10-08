/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#include "InstanceClientTCP.hpp"
#include "ServerTCP.hpp"

void InstanceClientTCP::start()
{
    std::cout << socket_.remote_endpoint().address().to_string() << std::endl;
    read();
}

void InstanceClientTCP::read()
{
    auto self(shared_from_this());
    auto Hrd =
    [this, self](boost::system::error_code ec, std::size_t length) {
        // If the client is disconnected
        if ((boost::asio::error::eof == ec) || (boost::asio::error::connection_reset == ec)) {
            std::cout << "Disconnected ID: " + std::to_string(id_) << std::endl;
            disconnected_ = true;
        } else {
            // If not disconnected, we print the received message
            dataLength_ = length;

            std::cout << "\033[31m[Client's message]:\033[0m ";
            std::cout.write(data_, length);
            std::cout << "\n";

            //write(std::string("Message well received on id: ") + std::to_string(this->id_));
            read();
        }
    };

    socket_.async_read_some(boost::asio::buffer(data_, max_length), Hrd);
}

void InstanceClientTCP::write(std::string msg)
{
    auto self(shared_from_this());
    auto Hwt =
    [this, self](boost::system::error_code ec, std::size_t) {
    if (!ec)
        read(); // FIXME ? On retire l'asynchrone ici non ?
    };

    /*std::cout << "\033[32mSend\033[0m " << msg << std::endl;
    for (auto &i : msg)
        printf("%d ", i);
    printf("\n");*/
    boost::asio::async_write(socket_, boost::asio::buffer(msg, msg.length()), Hwt);
}