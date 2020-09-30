/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Audio/Audio.hpp"

Audio::Audio() : Opus(), PortAudio()
{
    this->createEncoder();
    this->createDecoder();
    this->startStream();
}

