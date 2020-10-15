/*!
 * @file Audio/Encode.hpp
 * @brief Encode class
 * @author Emilien.D
 * @version 1.0
 * @date 08/10/2020
 *
 * The Encode class defines the methods and local variables for Opus encapsulation
*/

#ifndef BABEL_ENCODE_HPP
#define BABEL_ENCODE_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include <vector>
#include "opus.h"
#include "IEncode.hpp"
#include "BabelException.hpp"

class Encode : public IEncode
{
    public:
        Encode();
        void createEncoder() final;
        void createDecoder() final;
        void encodeData() final;
        void decodeData() final;
        void setCaptured(const std::vector<unsigned short> &);
        void setToDecode(const std::vector<unsigned char> &, const size_t &);
        [[nodiscard]] std::vector<unsigned char> getEncoded() const;
        [[nodiscard]] std::vector<unsigned short> getDecoded() const;
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

#endif //BABEL_ENCODE_HPP
