/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
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
        const int CHANNEL_NB = 1;
        //Frames data
        const int SAMPLE_RATE = 48000;
        const int FRAME_SIZE = 120;
};

#endif //BABEL_IENCODE_HPP
