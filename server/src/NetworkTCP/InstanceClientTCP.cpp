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
            std::cout << "Disconnected ID: " + std::to_string(id_) << std::endl;
            disconnected_ = true;
            /*cout << "shutdown" << endl;
            socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
            cout << "close" << endl;
            socket_.close();*/
        } else {
            dataLength_ = length;
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

    boost::asio::async_write(socket_, boost::asio::buffer(msg, msg.length()), Hwt);
}