/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include <iostream>
#include <utility>
#include <exception>
#include "Audio/PortAudio.hpp"

PortAudio::PortAudio() : captured(this->FRAME_SIZE * this->CHANNEL_NB),
                         decoded(this->FRAME_SIZE * this->CHANNEL_NB)
{
    this->init();
}

void PortAudio::init()
{
    std::cout << "Hello !" << std::endl;
    PaError err = Pa_Initialize();
    if (err != paNoError)
        throw std::exception();
}

void PortAudio::startStream()
{
    PaStreamParameters portAudioParameters[2];
    const PaDeviceInfo* deviceInfo[2];
    int numChannels;
    const int INPUT = 0;
    const int OUTPUT = 1;

    portAudioParameters[INPUT].device = Pa_GetDefaultInputDevice();
    portAudioParameters[OUTPUT].device = Pa_GetDefaultOutputDevice();
    deviceInfo[INPUT] = Pa_GetDeviceInfo(portAudioParameters[INPUT].device);
    deviceInfo[OUTPUT] = Pa_GetDeviceInfo(portAudioParameters[OUTPUT].device);
    if (deviceInfo[INPUT]->maxInputChannels < deviceInfo[OUTPUT]->maxOutputChannels)
        numChannels = deviceInfo[INPUT]->maxInputChannels;
    else
        numChannels = deviceInfo[OUTPUT]->maxOutputChannels;
    portAudioParameters[INPUT].channelCount = numChannels;
    portAudioParameters[INPUT].sampleFormat = paInt16;
    portAudioParameters[INPUT].suggestedLatency = deviceInfo[INPUT]->defaultHighInputLatency;
    portAudioParameters[INPUT].hostApiSpecificStreamInfo = nullptr;
    portAudioParameters[OUTPUT].channelCount = numChannels;
    portAudioParameters[OUTPUT].sampleFormat = paInt16;
    portAudioParameters[OUTPUT].suggestedLatency = deviceInfo[OUTPUT]->defaultHighOutputLatency;
    portAudioParameters[OUTPUT].hostApiSpecificStreamInfo = nullptr;
    //Open Stream
    PaError err = Pa_OpenStream(&this->stream, &portAudioParameters[INPUT], &portAudioParameters[OUTPUT],
        this->SAMPLE_RATE, 512, paClipOff, nullptr, nullptr);
    if (err != paNoError) {
        std::cout << err << std::endl;
        std::cout << "Error unavailable -> " << paDeviceUnavailable << std::endl;
        throw PortaudioError("Portaudio: ", " Error: " + static_cast<std::string>(Pa_GetErrorText(err)));
    }
    if (Pa_StartStream(stream) != paNoError)
        throw PortaudioError("Portaudio: ", " An error occurred while starting stream.");
}

void PortAudio::readStream()
{
    PaError err = Pa_ReadStream(stream, this->captured.data(), this->FRAME_SIZE);
    if (err != paNoError)
        throw PortaudioError("Portaudio: ", " Error: " + static_cast<std::string>(Pa_GetErrorText(err)));
}

void PortAudio::writeStream()
{
    PaError err = Pa_WriteStream(stream, decoded.data(), this->FRAME_SIZE);
    if (err != paNoError)
        throw PortaudioError("Portaudio: ", " Error: " + static_cast<std::string>(Pa_GetErrorText(err)));
}

void PortAudio::stopStream()
{
    PaError err = Pa_StopStream(stream);
    if (err)
        throw PortaudioError("Portaudio: ", " Error: " + static_cast<std::string>(Pa_GetErrorText(err)));
}

std::vector<unsigned short> PortAudio::getCaptured()
{
    return this->captured;
}

void PortAudio::setDecoded(std::vector<unsigned short> newDecoded)
{
    this->decoded = std::move(newDecoded);
}

void PortAudio::stop()
{
    Pa_Terminate();
}

PortAudio::~PortAudio()
{
    this->stop();
}
