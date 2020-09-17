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
    std::cout << audio.getDeviceNumber() << std::endl;
    PA_DeviceList a = audio.getDeviceInfo();
    return 0;
}
