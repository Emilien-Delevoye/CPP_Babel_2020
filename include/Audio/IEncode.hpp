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
        const int CHANNEL_NB = 2;
        const int SAMPLE_SIZE = 4;
        //Frames data
        const int SAMPLE_RATE = 48000;
        const int NUM_SECONDS = 3000;
        const int FRAMES_PER_BUFFER = 512;
        const int FRAME_SIZE = 120;
        const int BUFFER_SIZE = this->FRAMES_PER_BUFFER * this->CHANNEL_NB * this->SAMPLE_SIZE;

};

#endif //BABEL_IENCODE_HPP
