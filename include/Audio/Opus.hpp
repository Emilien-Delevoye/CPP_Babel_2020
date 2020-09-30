/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_OPUS_HPP
#define BABEL_OPUS_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include <vector>
#include "opus.h"
#include "IEncode.hpp"
#include "BabelException.hpp"

class Opus : public IEncode
{
    public:
        Opus();
        void createEncoder() final;
        void createDecoder() final;
        void encodeData() final;
        void decodeData() final;
        void setCaptured(std::vector<unsigned short>);
        void setToDecode(std::vector<unsigned char>, size_t);
        void setEncBytes(size_t);
        std::vector<unsigned char> getEncoded();
        std::vector<unsigned short> getDecoded();
        [[nodiscard]] size_t getEncBytes() const;
    private:
        std::vector<unsigned char> encoded;
        std::vector<unsigned short> captured;
        std::vector<unsigned short> decoded;
        std::vector<unsigned char> toDecode;
        OpusEncoder *enc;
        OpusDecoder *dec;
        size_t encBytes;
        size_t toDecBytes;
};

#endif //BABEL_OPUS_HPP
