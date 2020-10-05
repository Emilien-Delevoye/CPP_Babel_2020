/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Call.hpp"

int status_sound = 0;

int main(int argc, char **argv)
{
    status_sound = std::stoi(argv[3]);
    try {
        Call call("127.0.0.1", std::stoi(argv[1]), std::stoi(argv[2]));
    } catch (FatalError &e) {
        std::cerr << e.getComponent() << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Fatal Error: " << e.what() << std::endl;
    }
    return 0;
}
