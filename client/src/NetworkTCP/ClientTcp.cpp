/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#include "ClientTcp.hpp"
#include <memory>
#include <iostream>

ClientTCP::ClientTCP(std::string &ip, std::string &port) : resolver(io_context_)
{
    connect(ip, port);
}

void ClientTCP::connect(std::string &ip, std::string &port)
{
    boost::asio::connect(socket_, resolver.resolve(ip, port));
    async_read();
    thread_ = new std::thread([&] { io_context_.run(); });
}

void ClientTCP::async_read()
{
    //auto self(shared_from_this());
    auto Hrd =
    [this](boost::system::error_code ec, std::size_t length) {

        // If the client is disconnected
        if ((boost::asio::error::eof == ec) || (boost::asio::error::connection_reset == ec)) {
            std::cout << "Disconnected !" << std::endl;
        } else {
            // If not disconnected, we print the received message
            std::cout << "\033[31m[Server's message]:\033[0m ";
            std::cout.write(buffer_, length);
            dataLength_ = length;
            std::cout << "\n";
            isData = true;

            try {
                std::cout << "sanity check" << std::endl;
                auto tmp = std::string(buffer_, length);
                std::cout << "sanity check well passed" << std::endl;
            } catch (boost::archive::archive_exception &e) {
                std::cerr << "\033[31mERROR \033[0m" << e.what() << std::endl;
            }
            std::cout << std::endl;
        }
    };
    socket_.async_read_some(boost::asio::buffer(buffer_, max_length), Hrd);
}

std::string ClientTCP::read()
{
    char reply[max_length];
    size_t reply_length = socket_.read_some(boost::asio::buffer(reply, max_length));
    std::cout << std::string(reply, reply_length) << std::endl;
    return std::string(reply, reply_length);
}

void ClientTCP::write(std::string msg)
{
    std::cout << "send " << msg << std::endl;
    socket_.write_some(boost::asio::buffer(msg, msg.length()));
}

void ClientTCP::async_write(std::string msg)
{
    auto Hwt =
    [this](boost::system::error_code ec, std::size_t /*length*/) {
        if (!ec) {
            async_read();
        }
    };

    std::cout << "\033[32mSend\033[0m " << msg << std::endl;
    boost::asio::async_write(socket_, boost::asio::buffer(msg, msg.length()), Hwt);
}
