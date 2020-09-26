/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include <iostream>
#include <utility>
#include "PortAudio.hpp"

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
    PaError err = Pa_OpenDefaultStream(&this->stream, this->CHANNEL_NB, this->CHANNEL_NB, paInt16, this->SAMPLE_RATE,
        this->FRAME_SIZE, nullptr, nullptr);
    if (err != paNoError) {
        std::cout << err << std::endl;
        std::cout << "Error unavailable -> " << paDeviceUnavailable << std::endl;
        throw std::exception(Pa_GetErrorText(err));
    }
    if (Pa_StartStream(stream) != paNoError)
        throw std::exception("Start Stream");
}

void PortAudio::readStream()
{
    PaError err = Pa_ReadStream(stream, this->captured.data(), this->FRAME_SIZE);
    if (err != paNoError)
        throw std::exception(Pa_GetErrorText(err));
}

void PortAudio::writeStream()
{
    PaError err = Pa_WriteStream(stream, decoded.data(), this->FRAME_SIZE);
    if (err != paNoError)
        throw std::exception(Pa_GetErrorText(err));
}

void PortAudio::stopStream()
{
    PaError err = Pa_StopStream(stream);
    if (err)
        throw std::exception(Pa_GetErrorText(err));
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
