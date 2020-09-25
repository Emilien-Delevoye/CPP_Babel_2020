/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include <iostream>
#include "PortAudio.hpp"

PortAudio::PortAudio() : captured(this->FRAME_SIZE * this->CHANNEL_NB), decoded(this->FRAME_SIZE * this->CHANNEL_NB)
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

/*
void PortAudio::tmp()
{
    std::vector<unsigned char> encoded(this->FRAME_SIZE * this->CHANNEL_NB * 2);
    int opusError = OPUS_OK;
    opus_int32 enc_bytes;
    PaError err;

    OpusEncoder *enc = opus_encoder_create(this->SAMPLE_RATE, this->CHANNEL_NB, OPUS_APPLICATION_AUDIO, &opusError);
    if (opusError != OPUS_OK) {
        std::cerr << opusError << std::endl;
        throw std::exception("Opus encode creation");
    }

    OpusDecoder *dec = opus_decoder_create(this->SAMPLE_RATE, this->CHANNEL_NB, &opusError);
    if (opusError != OPUS_OK) {
        std::cerr << opusError << std::endl;
        throw std::exception("Opus decode creation");
    }

    for (int i = 0; i < (this->NUM_SECONDS * this->SAMPLE_RATE) / this->FRAMES_PER_BUFFER; ++i) {

        if ((enc_bytes = opus_encode(enc, reinterpret_cast<opus_int16 const *>(captured.data()),
            this->FRAME_SIZE, encoded.data(), encoded.size())) < 0)
            throw std::exception("opus_encode");
        if (opus_decode(dec, encoded.data(), enc_bytes, reinterpret_cast<opus_int16 *>(decoded.data()), this->FRAME_SIZE, 0) < 0)
            throw std::exception("opus_decode");
    }
    std::cout << "Wire off." << std::endl;
    err = Pa_StopStream(stream);
    if (err)
        throw std::exception(Pa_GetErrorText(err));
}
*/

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

void PortAudio::stop()
{
    Pa_Terminate();
}

PortAudio::~PortAudio()
{
    this->stop();
}
