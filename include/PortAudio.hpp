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

typedef struct PA_DeviceInfo_s {
    std::string name;
    int maxInputChannels;
    int maxOutputChannels;
    int API_index;
} PA_DeviceInfo;
typedef std::vector<PA_DeviceInfo> PA_DeviceList;

class PortAudio {
    public:
        PortAudio();
        int getDeviceNumber();
        PA_DeviceList getDeviceInfo();
        PaDeviceIndex getDefaultOutputDevice();
        PaDeviceIndex getDefaultInputDevice();
        void startStream();
        ~PortAudio();
    private:
        PA_DeviceList deviceList;
        int nbDevice = -1;
        const int PA_SAMPLE_TYPE = paFloat32;
        const int SAMPLE_SIZE = 4;
        const int SAMPLE_SILENCE = 0;
        const char *PRINTF_S_FLAG = "%.8f";
        const int numChannels = 2;

        const int SAMPLE_RATE = 48000;
        const int FRAMES_PER_BUFFER = 512;
        const int NUM_SECONDS = 3000;
        const int FRAME_SIZE = 120;
        const int BUFFER_SIZE = this->FRAMES_PER_BUFFER * this->numChannels * this->SAMPLE_SIZE;
};

#endif //BABEL_PORTAUDIO_HPP
