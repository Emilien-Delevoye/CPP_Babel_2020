/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#ifndef BABEL_AUDIO_HPP
#define BABEL_AUDIO_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include "Opus.hpp"
#include "PortAudio.hpp"

class Audio : public Opus, public PortAudio {
protected:
    explicit Audio();
};

#endif //BABEL_AUDIO_HPP
