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
    void init() final;
    [[nodiscard]] int getInputChannelNb() const override;
    [[nodiscard]] int getOutputChannelNb() const override;
    void startStream(int, int) final;
    void readStream() override;
    void writeStream() override;
    void stopStream() final;
    std::vector<unsigned short> getCaptured();
    void setDecoded(std::vector<unsigned short>);
    ~PortAudio();
private:
    void stop() final;
    enum _st {
            INPUT = 0,
            OUTPUT = 1
        };
    PaStreamParameters _portAudioParameters[2];
    const PaDeviceInfo* _deviceInfo[2];
    PaStream *_stream = nullptr;
    std::vector<unsigned short> _captured;
    std::vector<unsigned short> _decoded;
    int _numChannels[2];
    bool _init = false;
};

#endif //BABEL_PORTAUDIO_HPP
