/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/

#include "ClientTcp.hpp"
#include <memory>
#include <iostream>

using namespace std;

ClientTCP::ClientTCP(std::string &ip, std::string &port) : resolver(io_context_)
{}

bool ClientTCP::connect(std::string &ip, std::string &port)
{
    try {
        boost::asio::connect(socket_, resolver.resolve(ip, port));
    } catch (boost::wrapexcept<boost::system::system_error> &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

void ClientTCP::startAsyncRead()
{
    async_read();
    thread_ = new std::thread([&] { io_context_.run(); });
    printf("START READING\n");
}

void ClientTCP::async_read()
{
    //auto self(shared_from_this());
    auto Hrd =
    [this](boost::system::error_code ec, std::size_t length) {

        // If the client is disconnected
        if ((boost::asio::error::eof == ec) || (boost::asio::error::connection_reset == ec)) {
            std::cout << "Disconnected Client !" << std::endl;
            std::terminate();
        } else {
            dataLength_ = length;
            async_read();
        }
    };
    socket_.async_read_some(boost::asio::buffer(buffer_, max_length), Hrd);
}

std::string ClientTCP::read()
{
    char reply[max_length];
    size_t reply_length = socket_.read_some(boost::asio::buffer(reply, max_length));
    return std::string(reply, reply_length);
}

void ClientTCP::write(std::string msg)
{
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

    boost::asio::async_write(socket_, boost::asio::buffer(msg, msg.length()), Hwt);
}

void ClientTCP::disconnectThread()
{
    std::cout << "stop io context" << std::endl;
    io_context_.stop();
    cout << "join thread" << endl;
    thread_->join();
    cout << "thread joined" << endl;

    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    socket_.close();
    std::cout << "disconnect socket 2" << std::endl;
}

void ClientTCP::disconnect()
{
    std::cout << "close & shutdown socket" << std::endl;
    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    socket_.close();
    std::cout << "disconnect socket OK" << std::endl;
}
