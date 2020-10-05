/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Audio/Audio.hpp"
#include <iostream>

Audio::Audio() : Opus(), PortAudio()
{
    std::cout << "Start Audio()" << std::endl;
    try {
        this->createEncoder();
        this->createDecoder();
        this->startStream();
    } catch (OpusError &e) {
        throw FatalError("FatalError (Opus): ", e.what());
    } catch (PortaudioError &e) {
        throw FatalError("FatalError (PortAudio): ", e.what());
    } catch (std::exception &e) {
        throw FatalError("Fatal Error: ", e.what());
    }
}
