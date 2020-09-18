/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "PortAudio.hpp"
#include "opus.h"
#include <iostream>

PortAudio::PortAudio()
{
    std::cout << "Hello !" << std::endl;
    PaError err = Pa_Initialize();
    if (err != paNoError)
        throw std::exception();
}

void PortAudio::startStream() const
{
    std::vector<unsigned short> captured(this->FRAME_SIZE * this->numChannels);
    std::vector<unsigned short> decoded(this->FRAME_SIZE * this->numChannels);
    std::vector<unsigned char> encoded(this->FRAME_SIZE * this->numChannels * 2);
    PaStream *stream = nullptr;
    int opusError = OPUS_OK;
    opus_int32 enc_bytes;
    opus_int32 dec_bytes;
    PaError err;

    OpusEncoder *enc = opus_encoder_create(this->SAMPLE_RATE, numChannels, OPUS_APPLICATION_AUDIO, &opusError);
    if (opusError != OPUS_OK) {
        std::cerr << opusError << std::endl;
        throw std::exception("Opus encode creation");
    }

    OpusDecoder *dec = opus_decoder_create(this->SAMPLE_RATE, numChannels, &opusError);
    if (opusError != OPUS_OK) {
        std::cerr << opusError << std::endl;
        throw std::exception("Opus decode creation");
    }

    err = Pa_OpenDefaultStream(&stream, numChannels, numChannels, paInt16, this->SAMPLE_RATE,
        this->FRAME_SIZE, nullptr, nullptr);
    if (err != paNoError) {
        std::cout << err << std::endl;
        std::cout << "Error unavailable -> " << paDeviceUnavailable << std::endl;
        throw std::exception(Pa_GetErrorText(err));
    }
    std::cout << this->BUFFER_SIZE << std::endl;
    if (Pa_StartStream(stream) != paNoError)
        throw std::exception("Start Stream");
    for (int i = 0; i < (this->NUM_SECONDS * this->SAMPLE_RATE) / this->FRAMES_PER_BUFFER; ++i) {
        err = Pa_ReadStream(stream, captured.data(), this->FRAME_SIZE);
        if (err != paNoError)
            throw std::exception(Pa_GetErrorText(err));
        if ((enc_bytes = opus_encode(enc, reinterpret_cast<opus_int16 const *>(captured.data()),
            this->FRAME_SIZE, encoded.data(), encoded.size())) < 0)
            throw std::exception("opus_encode");
        if (opus_decode(dec, encoded.data(), enc_bytes, reinterpret_cast<opus_int16 *>(decoded.data()), this->FRAME_SIZE, 0) < 0)
            throw std::exception("opus_decode");
        err = Pa_WriteStream(stream, decoded.data(), this->FRAME_SIZE);
        if (err != paNoError)
            throw std::exception(Pa_GetErrorText(err));
    }
    std::cout << "Wire off." << std::endl;
    err = Pa_StopStream(stream);
    if (err)
        throw std::exception(Pa_GetErrorText(err));
}

PortAudio::~PortAudio()
{
    Pa_Terminate();
}
