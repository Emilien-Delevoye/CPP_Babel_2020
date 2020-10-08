/*!
 * @file Audio/AudioIO.cpp
 * @brief AudioIO class
 * @author Emilien.D
 * @version 1.0
 * @date 08/10/2020
 *
 * The AudioIO class reads the Input and set the Frame read in a vector, and takes a Frame to write it
*/

#include <iostream>
#include <utility>
#include <exception>
#include "Audio/AudioIO.hpp"

AudioIO::AudioIO() : _captured(this->FRAME_SIZE * this->CHANNEL_NB),
                         _decoded(this->FRAME_SIZE * this->CHANNEL_NB)
{
    this->init();
}

void AudioIO::init()
{
    this->_init = true;
    std::cout << "Hello !" << std::endl;
    PaError err = Pa_Initialize();
    if (err != paNoError)
        throw std::exception();
    this->_portAudioParameters[INPUT].device = Pa_GetDefaultInputDevice();
    this->_portAudioParameters[OUTPUT].device = Pa_GetDefaultOutputDevice();
    std::cout << "Device INPUT nb " << this->_portAudioParameters[INPUT].device << std::endl;
    std::cout << "Device OUTPUT nb " << this->_portAudioParameters[OUTPUT].device << std::endl;
    if (this->_portAudioParameters[INPUT].device < 0 || this->_portAudioParameters[OUTPUT].device < 0)
        throw FatalError("PortAudio", "Get default device");
    this->_deviceInfo[INPUT] = Pa_GetDeviceInfo(this->_portAudioParameters[INPUT].device);
    this->_deviceInfo[OUTPUT] = Pa_GetDeviceInfo(this->_portAudioParameters[OUTPUT].device);
    if (this->_deviceInfo[INPUT] == nullptr || this->_deviceInfo[OUTPUT] == nullptr)
        throw FatalError("PortAudio", "Get device info");

}

int AudioIO::getInputChannelNb() const
{
    if (this->_init)
        return this->_deviceInfo[INPUT]->maxInputChannels;
    else
        return 0;
}

int AudioIO::getOutputChannelNb() const
{
    if (this->_init)
        return this->_deviceInfo[OUTPUT]->maxOutputChannels;
    else
        return 0;
}

void AudioIO::startStream(int channelInputClient, int channelOutputClient)
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
    std::cout << "Name Output Device : " << this->_deviceInfo[OUTPUT]->name << std::endl;
    std::cout << "Name Input Device : " << this->_deviceInfo[INPUT]->name << std::endl;
    //Open Stream
    PaError err = Pa_OpenStream(&this->_stream, &this->_portAudioParameters[INPUT], &this->_portAudioParameters[OUTPUT],
        this->SAMPLE_RATE, 512, paClipOff, nullptr, nullptr);
    if (err != paNoError) {
        std::cout << err << std::endl;
        std::cout << "Error unavailable -> " << paDeviceUnavailable << std::endl;
        throw AudioIOError("Portaudio: ", " Error: " + static_cast<std::string>(Pa_GetErrorText(err)));
    }
    if (Pa_StartStream(_stream) != paNoError)
        throw AudioIOError("Portaudio: ", " An error occurred while starting stream.");
}

void AudioIO::readStream()
{
    PaError err = Pa_ReadStream(_stream, this->_captured.data(), this->FRAME_SIZE);
    if (err != paNoError)
        throw AudioIOError("Portaudio: ", " Error: " + static_cast<std::string>(Pa_GetErrorText(err)));
}

void AudioIO::writeStream()
{
    PaError err = Pa_WriteStream(_stream, _decoded.data(), this->FRAME_SIZE);
    if (err != paNoError) {
        if (err == paOutputUnderflowed)
            throw AudioIOError("Portaudio: ",
                " Error: " + static_cast<std::string>(Pa_GetErrorText(err)));
        else {
            std::cerr << "Bonjour, je suis un petit fils de flute" << std::endl;
            throw FatalError("PortAudio: ", static_cast<std::string>(Pa_GetErrorText(err)));
        }
    }
}

void AudioIO::stopStream()
{
    PaError err = Pa_StopStream(_stream);
    if (err)
        throw AudioIOError("Portaudio: ", " Error: " + static_cast<std::string>(Pa_GetErrorText(err)));
}

std::vector<unsigned short> AudioIO::getCaptured()
{
    return this->_captured;
}

void AudioIO::setDecoded(std::vector<unsigned short> newDecoded)
{
    this->_decoded = std::move(newDecoded);
}

void AudioIO::stop()
{
    Pa_Terminate();
}

AudioIO::~AudioIO()
{
    this->stop();
}
