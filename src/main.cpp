/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "PortAudio.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    PortAudio audio;
    try {
        audio.startStream();
    } catch (std::exception &e) {
        std::cerr << "Pas de chance " << e.what() << std::endl;
    }
    return 0;
}
