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
    int opusErrorCode = OPUS_OK;

    this->enc = opus_encoder_create(this->SAMPLE_RATE, this->CHANNEL_NB, OPUS_APPLICATION_AUDIO, &opusErrorCode);
    if (opusErrorCode != OPUS_OK) {
        std::cerr << opusErrorCode << std::endl;
        throw OpusError("Opus: ", "Error : Opus encode creation error.");
    }
    opusErrorCode = opus_encoder_ctl(this->enc, OPUS_SET_BITRATE(64000));
    //TMP -> Surveiller ce paramètre, il est intéressant sur le taux de compression
}

void Opus::createDecoder()
{
    int opusError = OPUS_OK;

    this->dec = opus_decoder_create(this->SAMPLE_RATE, this->CHANNEL_NB, &opusError);
    if (opusError != OPUS_OK) {
        std::cerr << opusError << std::endl;
        throw OpusError("Opus: ", "Error : Opus encode error.");
    }
}

void Opus::encodeData()
{
    this->encBytes = opus_encode(enc, reinterpret_cast<opus_int16 const *>(this->captured.data()), this->FRAME_SIZE, encoded.data(), encoded.size());
    //TMP -> Le parmaètre encBytes est très important pour l'utilisation de la lib
    if (this->encBytes < 0)
        throw OpusError("Opus: ", "Error : Opus encode error.");
}

void Opus::decodeData()
{
    if (opus_decode(dec, this->encoded.data(), this->encBytes, reinterpret_cast<opus_int16 *>(this->decoded.data()), this->FRAME_SIZE, 0) < 0)
        throw OpusError("Opus: ", "Error : Opus decode error.");
}

std::vector<unsigned char> Opus::getEncoded()
{
    return this->encoded;
}

void Opus::setCaptured(std::vector<unsigned short> inCaptured)
{
    this->captured = std::move(inCaptured);
}

std::vector<unsigned short> Opus::getDecoded()
{
    return this->decoded;
}

