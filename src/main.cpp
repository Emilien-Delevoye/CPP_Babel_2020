/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Call.hpp"

#include "NetworkTCP/server/ServerTCP.hpp"
#include "NetworkTCP/client/ClientTcp.hpp"
#include <boost/asio.hpp>
#include "NetworkTCP/Logger.hpp"

using boost::asio::ip::tcp;
using namespace std;

void server() {
    std::string defaultIP = "0.0.0.0";
    short defaultPort = 8080;

    try {
        ServerTCP s(defaultIP, defaultPort);
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

[[noreturn]] void client() {
    std::string defaultIP = "0.0.0.0";
    std::string defaultPort = "8080";

    ClientTCP client(defaultIP, defaultPort);

    while (true);
}

int main(int ac, char **av) {
    if (ac == 2)
        server();
    else
        client();
    return 0;
}