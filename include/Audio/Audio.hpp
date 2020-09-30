/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_AUDIO_HPP
#define BABEL_AUDIO_HPP

#include "Opus.hpp"
#include "PortAudio.hpp"

#define _WIN32_WINNT  0x0601

class Audio : public Opus, public PortAudio {
protected:
    explicit Audio();
};

#endif //BABEL_AUDIO_HPP
