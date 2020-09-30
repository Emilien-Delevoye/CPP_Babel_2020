/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_PORTAUDIO_HPP
#define BABEL_PORTAUDIO_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include <vector>
#include <string>
#include "portaudio.h"
#include "IAudio.hpp"
#include "BabelException.hpp"

class PortAudio: public IAudio {
    public:
        PortAudio();
        void startStream() final;
        void readStream() override;
        void writeStream() override;
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
