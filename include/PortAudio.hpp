/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_PORTAUDIO_HPP
#define BABEL_PORTAUDIO_HPP

#include <vector>
#include <string>
#include "portaudio.h"

typedef std::vector<PaDeviceInfo> PA_DeviceList;

class PortAudio {
    public:
        PortAudio();
        int getDeviceNumber();
        PA_DeviceList getDeviceInfo();
        ~PortAudio();
    private:
        int nbDevice = -1;
};

#endif //BABEL_PORTAUDIO_HPP
