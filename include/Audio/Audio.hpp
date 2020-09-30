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

class Audio : Opus, PortAudio {
    explicit Audio();
};

#endif //BABEL_AUDIO_HPP
