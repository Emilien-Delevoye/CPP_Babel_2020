/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_IAUDIO_HPP
#define BABEL_IAUDIO_HPP

class IAudio {
    public:
        virtual void init() = 0;
        virtual void startStream() = 0;
        virtual void readStream() = 0;
        virtual void writeStream() = 0;
        virtual void stopStream() = 0;
        virtual void stop() = 0;
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

#endif //BABEL_IAUDIO_HPP
