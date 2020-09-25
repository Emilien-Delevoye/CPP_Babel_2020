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

class Audio: public IAudio {
    public:
        Audio();
        void startStream() final;
        void readStream() final;
        void writeStream() final;
        void stopStream() final;
        ~Audio();
    private:
        void init() final;
        void stop() final;
        PaStream *stream = nullptr;
        std::vector<unsigned short> captured;
        std::vector<unsigned short> decoded;
};

#endif //BABEL_PORTAUDIO_HPP
