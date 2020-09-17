/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "PortAudio.hpp"
#include <iostream>

PortAudio::PortAudio()
{
    std::cout << "Hello !" << std::endl;
    PaError err = Pa_Initialize();
    if (err != 0)
        throw std::exception();
}

int PortAudio::getDeviceNumber()
{
    int nbDevices = Pa_GetDeviceCount();

    if (nbDevices < 0) {
        std::fprintf(stderr, "ERROR (getDeviceNumber): 0x%x\n", nbDevices);
        throw std::exception();
    }
    this->nbDevice = nbDevices;
    return nbDevices;
}

std::vector<PaDeviceInfo> PortAudio::getDeviceInfo()
{
    PA_DeviceList vecDeviceInfo;

    this->getDeviceNumber();
    vecDeviceInfo.reserve(this->nbDevice);
    for (int i = 0; i < this->nbDevice; ++i)
        vecDeviceInfo.push_back(*Pa_GetDeviceInfo(i));
    return vecDeviceInfo;
}

PortAudio::~PortAudio()
{
    Pa_Terminate();
}
