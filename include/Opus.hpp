/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_OPUS_HPP
#define BABEL_OPUS_HPP

#include "IEncode.hpp"
#include <opus.h>
#include <vector>

class Opus : public IEncode
{
    public:
        Opus();
        void init() final;
        void createEncoder() final;
        void createDecoder() final;
        void encodeData() final;
        void decodeData() final;
    private:
        std::vector<unsigned char> encoded;
        std::vector<unsigned short> captured;
        std::vector<unsigned short> decoded;
        OpusEncoder *enc;
        OpusDecoder *dec;
        opus_int32 encBytes;
};

#endif //BABEL_OPUS_HPP
