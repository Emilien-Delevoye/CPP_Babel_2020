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
    if (err != paNoError)
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

PA_DeviceList PortAudio::getDeviceInfo()
{
    PA_DeviceList vecDeviceInfo;

    this->getDeviceNumber();
    vecDeviceInfo.reserve(this->nbDevice);
    for (int i = 0; i < this->nbDevice; ++i) {
        const PaDeviceInfo *info = Pa_GetDeviceInfo(i);
        PA_DeviceInfo deviceInfo = {.name = std::string(info->name), .maxInputChannels = info->maxInputChannels,
            .maxOutputChannels = info->maxOutputChannels, .API_index = info->hostApi};
        vecDeviceInfo.push_back(deviceInfo);
    }
    this->deviceList = vecDeviceInfo;
    for (auto &a : vecDeviceInfo) {
        std::cout << a.name << std::endl;
        std::cout << a.maxInputChannels << std::endl;
        std::cout << a.maxOutputChannels << std::endl;
        std::cout << "=======================" << std::endl;
    }
    return vecDeviceInfo;
}

PaDeviceIndex PortAudio::getDefaultOutputDevice()
{
    return (Pa_GetDefaultOutputDevice());
}

PaDeviceIndex PortAudio::getDefaultInputDevice()
{
    return (Pa_GetDefaultInputDevice());
}

void PortAudio::startStream()
{
    PaStream *stream = nullptr;
    PaStreamParameters inputParameters = {.device = Pa_GetDefaultInputDevice()};
    PaStreamParameters outputParameters = {.device = Pa_GetDefaultOutputDevice()};
    const PaDeviceInfo *inputInfo = Pa_GetDeviceInfo(inputParameters.device);
    const PaDeviceInfo *outputInfo = Pa_GetDeviceInfo(outputParameters.device);
    int numChannels = inputInfo->maxInputChannels < outputInfo->maxOutputChannels ? inputInfo->maxInputChannels : outputInfo->maxOutputChannels;
    PaError err;

    if (inputParameters.device == paNoDevice || outputParameters.device == paNoDevice)
        throw std::exception("Ah bon");
    printf( "Name: %s\n", inputInfo->name);
    printf( "   LL: %g s\n", inputInfo->defaultLowInputLatency);
    printf( "   HL: %g s\n", inputInfo->defaultHighInputLatency);

    printf( "Name: %s\n", outputInfo->name );
    printf( "   LL: %g s\n", outputInfo->defaultLowOutputLatency );
    printf( "   HL: %g s\n", outputInfo->defaultHighOutputLatency );

    std::printf("Num channels = %d.\n", numChannels);
    inputParameters.channelCount = numChannels;
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = inputInfo->defaultHighInputLatency;
    inputParameters.hostApiSpecificStreamInfo = nullptr;

    outputParameters.channelCount = numChannels;
    outputParameters.sampleFormat = PA_SAMPLE_TYPE;
    outputParameters.suggestedLatency = outputInfo->defaultHighOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = nullptr;
    err = Pa_OpenStream(&stream, &inputParameters, &outputParameters, this->SAMPLE_RATE, this->FRAMES_PER_BUFFER, paClipOff,
        nullptr, nullptr);
    if (err != paNoError) {
        std::cout << err << std::endl;
        std::cout << "Error unavailable -> " << paDeviceUnavailable << std::endl;
        throw std::exception(Pa_GetErrorText(err));
    }
    char *sampleBlock = new char [(this->FRAMES_PER_BUFFER * numChannels * this->SAMPLE_SIZE)];
    if (Pa_StartStream(stream) != paNoError)
        throw std::exception("Start Stream");
    for (int i = 0; i < (this->NUM_SECONDS * this->SAMPLE_RATE) / this->FRAMES_PER_BUFFER; ++i) {
        err = Pa_WriteStream(stream, sampleBlock, this->FRAMES_PER_BUFFER);
        if (err != paNoError)
            throw std::exception(Pa_GetErrorText(err));
        err = Pa_ReadStream(stream, sampleBlock, this->FRAMES_PER_BUFFER);
        if (err != paNoError)
            throw std::exception(Pa_GetErrorText(err));
    }
    std::cout << "Wire off." << std::endl;
    err = Pa_StopStream(stream);
    if (err)
        throw std::exception(Pa_GetErrorText(err));
    delete[] sampleBlock;
}

PortAudio::~PortAudio()
{
    Pa_Terminate();
}
