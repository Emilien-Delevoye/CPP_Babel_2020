/*!
 * @file Audio/IEncode.hpp
 * @brief IEncode interface
 * @author Emilien.D
 * @version 1.0
 * @date 08/10/2020
 *
 * The IEncode interface describes the methods and constants for the Encode class
*/

#ifndef BABEL_IENCODE_HPP
#define BABEL_IENCODE_HPP

class IEncode
{
    public:
        virtual void createEncoder() = 0;
        virtual void createDecoder() = 0;
        virtual void encodeData() = 0;
        virtual void decodeData() = 0;
    protected:
        //channel and sample data
        const int CHANNEL_NB = 2;
        //Frames data
        const int SAMPLE_RATE = 48000;
        const int FRAME_SIZE = 120;
};

#endif //BABEL_IENCODE_HPP
