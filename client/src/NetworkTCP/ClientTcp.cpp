/*!
 * @file ClientTCP.cpp
 * @brief Client manager
 * @author Cyprien.R
* @version 1.0
 * @date 10/10/2020
*/

#include "ClientTcp.hpp"
#include <memory>
#include <iostream>
#include <regex>

using namespace std;

/*!
 * \brief ClientTCP constructor
 * \param std::string ip
 * \param std::string port
 *
 * Construct the class
*/

ClientTCP::ClientTCP(std::string &ip, std::string &port) : resolver(io_context_), deadline_(io_context_)
{}

/*!
 * \brief check_deadline method
 *
 * This method is here to check if the connection time is not over the imposed time.
*/

void ClientTCP::check_deadline()
{
    if (deadline_.expires_at() <= deadline_timer::traits_type::now()) {
        boost::system::error_code ignored_ec;
        socket_.close(ignored_ec);
        deadline_.expires_at(boost::posix_time::pos_infin);
    }
    deadline_.async_wait(bind(&ClientTCP::check_deadline, this));
}

/*!
 * \brief connectTimeOut method
 * \param std::string ip
 * \param std::string port
 * \param time max
 *
 * This method connect the client with connection time out which equals "time max"
*/

void ClientTCP::connectTimeOut(const std::string &ip, const std::string &port, const boost::posix_time::time_duration& timeout)
{
    tcp::resolver::query query(ip, port);
    tcp::resolver::iterator iter = tcp::resolver(io_context_).resolve(query);

    deadline_.expires_from_now(timeout);
    check_deadline();
    boost::system::error_code ec = boost::asio::error::would_block;
    boost::asio::async_connect(socket_, iter, var(ec) = _1);

    do io_context_.run_one();
    while (ec == boost::asio::error::would_block);

    if (ec || !socket_.is_open())
        throw boost::system::system_error(ec ? ec : boost::asio::error::operation_aborted);
    deadline_.expires_at(boost::posix_time::max_date_time);
}

/*!
 * \brief connect method
 * \param std::string ip
 * \param std::string port
 * \return true if the client is connect, false otherwise
 *
 * This method connect the client to the server.
*/

bool ClientTCP::connect(std::string &ip, std::string &port)
{
    if (!std::regex_match(ip, std::regex(R"(\d+.\d+.\d+.\d+)")))
        return false;
    try {
        connectTimeOut(ip, port, boost::posix_time::seconds(1));
    } catch (boost::system::system_error &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

/*!
 * \brief startAsyncRead method
 *
 * This method start the asynchrone read to get server messages'.
*/

void ClientTCP::startAsyncRead()
{
    async_read();
    thread_ = new std::thread([&] { io_context_.run(); });
    printf("START READING\n");
}

/*!
 * \brief async_read method
 *
 * This method setup the function used in asynchrone read.
*/

void ClientTCP::async_read()
{
    //auto self(shared_from_this());
    auto Hrd =
    [this](boost::system::error_code ec, std::size_t length) {

        // If the client is disconnected
        if ((boost::asio::error::eof == ec) || (boost::asio::error::connection_reset == ec)) {
            std::cout << "Disconnected Client !" << std::endl;
            justDisconnected_ = true;
        } else {
            dataLength_ = length;
            async_read();
        }
    };
    socket_.async_read_some(boost::asio::buffer(buffer_, max_length), Hrd);
}

/*!
 * \brief read method
 *
 * This method read and wait a message from the server.
*/

std::string ClientTCP::read()
{
    char reply[max_length];
    size_t reply_length = socket_.read_some(boost::asio::buffer(reply, max_length));
    return std::string(reply, reply_length);
}

/*!
 * \brief write method
 *
 * This method send a message to the server.
*/

void ClientTCP::write(std::string msg)
{
    socket_.write_some(boost::asio::buffer(msg, msg.length()));
}

/*!
 * \brief async_write method
 *
 * This method send an asynchrone message to the server.
*/

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

/*!
 * \brief disconnectThread method
 *
 * This method disconnected the client from the server and stop the thread.
*/

void ClientTCP::disconnectThread()
{
    std::cout << "stop io context" << std::endl;
    io_context_.stop();
    cout << "join thread" << endl;
    thread_->join();
    cout << "thread joined" << endl;

    try {
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        socket_.close();
    } catch (boost::system::system_error &e) {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "disconnect socket 2" << std::endl;
}

/*!
 * \brief disconnect method
 *
 * This method disconnected the client from the server.
*/

void ClientTCP::disconnect()
{
    std::cout << "close & shutdown socket" << std::endl;
    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    socket_.close();
    std::cout << "disconnect socket OK" << std::endl;
}
