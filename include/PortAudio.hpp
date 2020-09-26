/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_PORTAUDIO_HPP
#define BABEL_PORTAUDIO_HPP

#include <vector>
#include <string>
#include "portaudio.h"
#include "IAudio.hpp"

class PortAudio: public IAudio {
    public:
        PortAudio();
        void startStream() final;
        void readStream() final;
        void writeStream() final;
        void stopStream() final;
        std::vector<unsigned short> getCaptured();
        void setDecoded(std::vector<unsigned short>);
        ~PortAudio();
    private:
        void init() final;
        void stop() final;
        PaStream *stream = nullptr;
        std::vector<unsigned short> captured;
        std::vector<unsigned short> decoded;
};

#endif //BABEL_PORTAUDIO_HPP
