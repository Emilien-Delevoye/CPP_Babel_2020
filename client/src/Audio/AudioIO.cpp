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

/*!
* \brief Constructor for AudioIO, it calls the init override from IAudio interface
*/

AudioIO::AudioIO() : _captured(this->FRAME_SIZE * this->CHANNEL_NB),
                         _decoded(this->FRAME_SIZE * this->CHANNEL_NB)
{
    this->init();
}

/*!
* \brief AudioIO::init() init PortAudio and the 2 default devices (Input and Output)
*/

void AudioIO::init()
{
    this->_init = true;
    PaError err = Pa_Initialize();
    if (err != paNoError)
        throw std::exception();
    this->_portAudioParameters[INPUT].device = Pa_GetDefaultInputDevice();
    this->_portAudioParameters[OUTPUT].device = Pa_GetDefaultOutputDevice();
    if (this->_portAudioParameters[INPUT].device < 0 || this->_portAudioParameters[OUTPUT].device < 0) {
        std::cerr << "PortAudio (Error) : Get default device" << std::endl;
        this->_fatalError = true;
        return;
    }
    this->_deviceInfo[INPUT] = Pa_GetDeviceInfo(this->_portAudioParameters[INPUT].device);
    this->_deviceInfo[OUTPUT] = Pa_GetDeviceInfo(this->_portAudioParameters[OUTPUT].device);
    if (this->_deviceInfo[INPUT] == nullptr || this->_deviceInfo[OUTPUT] == nullptr) {
        std::cerr << "PortAudio (Error) : Get default info" << std::endl;
        this->_fatalError = true;
        return;
    }
}

/*!
* \brief AudioIO::startStream opens the streams and starts it, the microphone and the speakers are active after it
* \param channelInputClient is the number of input channel(s) from the destination client
* \param channelOutputClient is the number of output channel(s) from the destination client
*/

void AudioIO::startStream(int channelInputClient, int channelOutputClient)
{
    if (this->_fatalError)
        return;
    this->_numChannels[INPUT] = (this->_deviceInfo[INPUT]->maxInputChannels < channelOutputClient ? this->_deviceInfo[INPUT]->maxInputChannels : channelOutputClient);
    this->_numChannels[OUTPUT] = (this->_deviceInfo[OUTPUT]->maxOutputChannels < channelInputClient ? this->_deviceInfo[OUTPUT]->maxOutputChannels : channelInputClient);
    this->_portAudioParameters[INPUT].channelCount = this->_numChannels[INPUT];
    this->_portAudioParameters[INPUT].sampleFormat = paInt16;
    this->_portAudioParameters[INPUT].suggestedLatency = this->_deviceInfo[INPUT]->defaultLowInputLatency;
    this->_portAudioParameters[INPUT].hostApiSpecificStreamInfo = nullptr;
    this->_portAudioParameters[OUTPUT].channelCount = this->_numChannels[OUTPUT];
    this->_portAudioParameters[OUTPUT].sampleFormat = paInt16;
    this->_portAudioParameters[OUTPUT].suggestedLatency = this->_deviceInfo[OUTPUT]->defaultHighOutputLatency;
    this->_portAudioParameters[OUTPUT].hostApiSpecificStreamInfo = nullptr;
    //Open Stream
    PaError err = Pa_OpenStream(&this->_streamInput, &this->_portAudioParameters[INPUT], nullptr,
        this->SAMPLE_RATE, 512, paClipOff, nullptr, nullptr);
    if (err != paNoError)
        throw AudioIOError("Portaudio: ", " Error: " + static_cast<std::string>(Pa_GetErrorText(err)));
    err = Pa_OpenStream(&this->_streamOutput, nullptr, &this->_portAudioParameters[OUTPUT],
        this->SAMPLE_RATE, 512, paClipOff, nullptr, nullptr);
    if (err != paNoError)
        throw AudioIOError("Portaudio: ", " Error: " + static_cast<std::string>(Pa_GetErrorText(err)));
    if (Pa_StartStream(_streamInput) != paNoError)
        throw AudioIOError("Portaudio: ", " An error occurred while starting input stream.");
    if (Pa_StartStream(_streamOutput) != paNoError)
        throw AudioIOError("Portaudio: ", " An error occurred while starting output stream.");
}

/*!
* \brief AudioIO::readStream reads a frame from the microphone and set it to a private vector which can be get by getCaptured().
*/

void AudioIO::readStream()
{
    if (this->_fatalError)
        return;
    PaError err = Pa_ReadStream(_streamInput, this->_captured.data(), this->FRAME_SIZE);
    if (err != paNoError)
        throw AudioIOError("Portaudio: ", " Error: " + static_cast<std::string>(Pa_GetErrorText(err)));
}

/*!
* \brief AudioIO::writeStream write the decoded stream from setDecoded to the speakers
*/

void AudioIO::writeStream()
{
    if (this->_fatalError)
        return;
    PaError err = Pa_WriteStream(_streamOutput, _decoded.data(), this->FRAME_SIZE);
    if (err != paNoError)
        throw AudioIOError("Portaudio: ",
            " Error: " + static_cast<std::string>(Pa_GetErrorText(err)));
}

/*!
* \brief AudioIO::stopStream stops the input and output streams
*/

void AudioIO::stopStream()
{
    if (_streamInput) {
        PaError err = Pa_StopStream(_streamInput);
        if (err)
            throw AudioIOError("Portaudio: ", " Error: " + static_cast<std::string>(Pa_GetErrorText(err)));
    }
    if (_streamOutput) {
        PaError err = Pa_StopStream(_streamOutput);
        if (err)
            throw AudioIOError("Portaudio: ", " Error: " + static_cast<std::string>(Pa_GetErrorText(err)));
    }
}

/*!
* \brief AudioIO::getCaptured returns the captured data from AudioIO::readStream
*/

std::vector<unsigned short> AudioIO::getCaptured()
{
    return this->_captured;
}

/*!
* \brief AudioIO::setDecoded set the decoded stream from the Encode class, this needs to be set before AudioIO::writeStream
* \param newDecoded is the decoded vector from the Encode class
*/

void AudioIO::setDecoded(std::vector<unsigned short> newDecoded)
{
    this->_decoded = std::move(newDecoded);
}

void AudioIO::stop()
{
    stopStream();
    Pa_Terminate();
}

/*!
* \brief AudioIO::~AudioIO stops the AudioIO class
*/

AudioIO::~AudioIO()
{
    this->stop();
}
