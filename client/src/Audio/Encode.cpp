/*!
 * @file Audio/Encode.cpp
 * @brief Encode class
 * @author Emilien.D
 * @version 1.0
 * @date 08/10/2020
 *
 * Definitions for the Encode methods
*/

#include "Audio/Encode.hpp"
#include <iostream>
#include <utility>

/*!
* \brief Encode::Encode constructor sets the default values
*/

Encode::Encode() : encoded(this->FRAME_SIZE * this->CHANNEL_NB * 2),
               captured(this->FRAME_SIZE * this->CHANNEL_NB),
               decoded(this->FRAME_SIZE * this->CHANNEL_NB)
{
    this->enc = nullptr;
    this->dec = nullptr;
    this->encBytes = 0;
}

/*!
* \brief Encode::createEncoder init the encoder
*/

void Encode::createEncoder()
{
    int opusErrorCode = OPUS_OK;

    this->enc = opus_encoder_create(this->SAMPLE_RATE, this->CHANNEL_NB, OPUS_APPLICATION_AUDIO, &opusErrorCode);
    if (opusErrorCode != OPUS_OK) {
        throw EncodeError("Encode: ", opus_strerror(opusErrorCode));
    }
    opusErrorCode = opus_encoder_ctl(this->enc, OPUS_SET_BITRATE(64000));
    //TMP -> Surveiller ce paramètre, il est intéressant sur le taux de compression
}

/*!
* \brief Encode::createDecoder init the decoder
*/

void Encode::createDecoder()
{
    int opusError = OPUS_OK;

    this->dec = opus_decoder_create(this->SAMPLE_RATE, this->CHANNEL_NB, &opusError);
    if (opusError != OPUS_OK) {
        std::cerr << opusError << std::endl;
        throw EncodeError("Encode: ", "Error : Encode encode error.");
    }
}

/*!
* \brief Encode::encodeData encode the data set by setCaptured setter
*/

void Encode::encodeData()
{
    this->encBytes = opus_encode(enc, reinterpret_cast<opus_int16 const *>(this->captured.data()), this->FRAME_SIZE, encoded.data(), static_cast<opus_int32>(encoded.size()));
    //TMP -> Le paramètre encBytes est très important pour l'utilisation de la lib
    if (this->encBytes < 0)
        throw EncodeError("Encode: ", "Error : Encode encode error.");
}

/*!
* \brief Encode::decodeData decode the data set by setToDecode setter
*/

void Encode::decodeData()
{
    if (opus_decode(dec, this->toDecode.data(), static_cast<opus_int32>(this->toDecBytes), reinterpret_cast<opus_int16 *>(this->decoded.data()), this->FRAME_SIZE, 0) < 0)
        throw EncodeError("Encode: ", "Error : Encode decode error.");
}

/*!
* \brief Encode::getEncoded return the encoded vector
*/

std::vector<unsigned char> Encode::getEncoded()
{
    return this->encoded;
}

/*!
* \brief Encode::setToDecode set the encoded vector to decode
* \param intToDecode is the encoded vector
* \param encBytesFromUDP is the number of bytes to decode 
*/

void Encode::setToDecode(std::vector<unsigned char> inToDecode, size_t encBytesFromUDP)
{
    this->toDecode = std::move(inToDecode);
    this->toDecBytes = encBytesFromUDP;
}

/*!
* \brief Encode::setCaptured set the vector to encode
* \param inCaptured is the vector to encode
*/

void Encode::setCaptured(std::vector<unsigned short> inCaptured)
{
    this->captured = std::move(inCaptured);
}

/*!
* \brief Encode::getDecoded returns the vector decoded
*/

std::vector<unsigned short> Encode::getDecoded()
{
    return this->decoded;
}

/*!
* \brief Encode::getEncBytes returns the number of bytes encoded
*/

size_t Encode::getEncBytes() const
{
    return this->encBytes;
}

