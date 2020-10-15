/*!
 * @file InstanceClientTCP.cpp
 * @brief Client manager
 * @author Cyprien.R
* @version 1.0
 * @date 10/10/2020
*/

#include "InstanceClientTCP.hpp"

using namespace std;

/*!
 * \brief InstanceClientTCP constructor
 * \param tcp::socket socket
 * \param int id
 *
 * Construct the class which is one connected client.
*/

InstanceClientTCP::InstanceClientTCP(tcp::socket socket, int id) : socket_(std::move(socket)), id_(id)
{
    clearReceivedData();
    ip_ = socket_.remote_endpoint().address().to_string();
}

/*!
 * \brief startAsyncRead method
 *
 * This method setup the function that will be used to read newly received messages.
 * This method start async read
*/

void InstanceClientTCP::startAsyncRead()
{
    auto self(shared_from_this());
    auto Hrd =
    [this, self](boost::system::error_code ec, std::size_t length) {
        if ((boost::asio::error::eof == ec) || (boost::asio::error::connection_reset == ec)) {
            std::cout << "\033[31;1mDisconnected ID:\033[0m " + std::to_string(id_) << std::endl;
            disconnected_ = true;
        } else {
            dataLength_ = length;
            startAsyncRead();
        }
    };
    socket_.async_read_some(boost::asio::buffer(data_, max_length), Hrd);
}

/*!
 * \brief write method
 *
 * This method allow the server to send message to connected clients.
*/

void InstanceClientTCP::write(const std::string& msg)
{
    boost::asio::write(socket_, boost::asio::buffer(msg, msg.length()));
}