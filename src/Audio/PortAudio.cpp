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

PortAudio::PortAudio() : _captured(this->FRAME_SIZE * this->CHANNEL_NB),
                         _decoded(this->FRAME_SIZE * this->CHANNEL_NB)
{
    this->init();
}

void PortAudio::init()
{
    this->_init = true;
    std::cout << "Hello !" << std::endl;
    PaError err = Pa_Initialize();
    if (err != paNoError)
        throw std::exception();
    this->_portAudioParameters[INPUT].device = Pa_GetDefaultInputDevice();
    this->_portAudioParameters[OUTPUT].device = Pa_GetDefaultOutputDevice();
    this->_deviceInfo[INPUT] = Pa_GetDeviceInfo(this->_portAudioParameters[INPUT].device);
    this->_deviceInfo[OUTPUT] = Pa_GetDeviceInfo(this->_portAudioParameters[OUTPUT].device);
}

int PortAudio::getInputChannelNb() const
{
    if (this->_init)
        return this->_deviceInfo[INPUT]->maxInputChannels;
    else
        return 0;
}

int PortAudio::getOutputChannelNb() const
{
    if (this->_init)
        return this->_deviceInfo[OUTPUT]->maxOutputChannels;
    else
        return 0;
}

void PortAudio::startStream(int channelInputClient, int channelOutputClient)
{
    this->_numChannels[INPUT] = (this->_deviceInfo[INPUT]->maxInputChannels < channelOutputClient ? this->_deviceInfo[INPUT]->maxInputChannels : channelOutputClient);
    this->_numChannels[OUTPUT] = (this->_deviceInfo[OUTPUT]->maxOutputChannels < channelInputClient ? this->_deviceInfo[OUTPUT]->maxOutputChannels : channelInputClient);
    this->_portAudioParameters[INPUT].channelCount = this->_numChannels[INPUT];
    this->_portAudioParameters[INPUT].sampleFormat = paInt16;
    this->_portAudioParameters[INPUT].suggestedLatency = this->_deviceInfo[INPUT]->defaultHighInputLatency;
    this->_portAudioParameters[INPUT].hostApiSpecificStreamInfo = nullptr;
    this->_portAudioParameters[OUTPUT].channelCount = this->_numChannels[OUTPUT];
    this->_portAudioParameters[OUTPUT].sampleFormat = paInt16;
    this->_portAudioParameters[OUTPUT].suggestedLatency = this->_deviceInfo[OUTPUT]->defaultHighOutputLatency;
    this->_portAudioParameters[OUTPUT].hostApiSpecificStreamInfo = nullptr;
    //Open Stream
    PaError err = Pa_OpenStream(&this->_stream, &this->_portAudioParameters[INPUT], &this->_portAudioParameters[OUTPUT],
        this->SAMPLE_RATE, 512, paClipOff, nullptr, nullptr);
    if (err != paNoError) {
        std::cout << err << std::endl;
        std::cout << "Error unavailable -> " << paDeviceUnavailable << std::endl;
        throw PortaudioError("Portaudio: ", " Error: " + static_cast<std::string>(Pa_GetErrorText(err)));
    }
    if (Pa_StartStream(_stream) != paNoError)
        throw PortaudioError("Portaudio: ", " An error occurred while starting stream.");
}

void PortAudio::readStream()
{
    PaError err = Pa_ReadStream(_stream, this->_captured.data(), this->FRAME_SIZE);
    if (err != paNoError)
        throw PortaudioError("Portaudio: ", " Error: " + static_cast<std::string>(Pa_GetErrorText(err)));
}

void PortAudio::writeStream()
{
    PaError err = Pa_WriteStream(_stream, _decoded.data(), this->FRAME_SIZE);
    if (err != paNoError)
        throw PortaudioError("Portaudio: ", " Error: " + static_cast<std::string>(Pa_GetErrorText(err)));
}

void PortAudio::stopStream()
{
    PaError err = Pa_StopStream(_stream);
    if (err)
        throw PortaudioError("Portaudio: ", " Error: " + static_cast<std::string>(Pa_GetErrorText(err)));
}

std::vector<unsigned short> PortAudio::getCaptured()
{
    return this->_captured;
}

void PortAudio::setDecoded(std::vector<unsigned short> newDecoded)
{
    this->_decoded = std::move(newDecoded);
}

void PortAudio::stop()
{
    Pa_Terminate();
}

PortAudio::~PortAudio()
{
    this->stop();
}
