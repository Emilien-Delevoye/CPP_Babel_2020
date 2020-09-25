/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include <Opus.hpp>
#include <iostream>

Opus::Opus() : encoded(this->FRAME_SIZE * this->CHANNEL_NB * 2),
               captured(this->FRAME_SIZE * this->CHANNEL_NB),
               decoded(this->FRAME_SIZE * this->CHANNEL_NB)
{
    this->enc = nullptr;
    this->dec = nullptr;
    this->encBytes = 0;
    this->init();
}

void Opus::init()
{
}

void Opus::createEncoder()
{
    int opusError = OPUS_OK;

    this->enc = opus_encoder_create(this->SAMPLE_RATE, this->CHANNEL_NB, OPUS_APPLICATION_AUDIO, &opusError);
    if (opusError != OPUS_OK) {
        std::cerr << opusError << std::endl;
        throw std::exception("Opus encode creation");
    }
}

void Opus::createDecoder()
{
    int opusError = OPUS_OK;

    this->dec = opus_decoder_create(this->SAMPLE_RATE, this->CHANNEL_NB, &opusError);
    if (opusError != OPUS_OK) {
        std::cerr << opusError << std::endl;
        throw std::exception("Opus decode creation");
    }
}

void Opus::encodeData()
{
    this->encBytes = opus_encode(enc, reinterpret_cast<opus_int16 const *>(this->captured.data()), this->FRAME_SIZE, encoded.data(), encoded.size());
    if (this->encBytes < 0)
        throw std::exception("opus_encode");
}

void Opus::decodeData()
{
    if (opus_decode(dec, this->encoded.data(), this->encBytes, reinterpret_cast<opus_int16 *>(this->decoded.data()), this->FRAME_SIZE, 0) < 0)
        throw std::exception("opus_decode");
}

