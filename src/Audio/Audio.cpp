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
        std::cerr << e.what() << std::endl;
        throw FatalError("FatalError (Opus): ", std::string(e.what()));
    } catch (PortaudioError &e) {
        std::cerr << e.what() << std::endl;
        throw FatalError("FatalError (PortAudio): ", std::string(e.what()));
    } catch (std::exception &e) {
        std::cerr << "Pas Pouet 2 " << e.what() << std::endl;
    }
}
