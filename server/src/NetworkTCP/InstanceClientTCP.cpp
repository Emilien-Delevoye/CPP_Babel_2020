/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#include "InstanceClientTCP.hpp"
#include "ServerTCP.hpp"

using namespace std;

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
        if ((boost::asio::error::eof == ec) || (boost::asio::error::connection_reset == ec)) {
            std::cout << "\033[31;1mDisconnected ID:\033[0m " + std::to_string(id_) << std::endl;
            disconnected_ = true;
        } else {
            dataLength_ = length;
            read();
        }
    };
    socket_.async_read_some(boost::asio::buffer(data_, max_length), Hrd);
}

void InstanceClientTCP::write(std::string msg)
{
    boost::asio::write(socket_, boost::asio::buffer(msg, msg.length()));
}