/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Audio/Audio.hpp"
#include <iostream>

Audio::Audio() : Encode(), AudioIO()
{
    std::cout << "Start Audio()" << std::endl;
    try {
        this->createEncoder();
        this->createDecoder();
        this->startStream(2, 2); //TODO: Mettre le nombre de channel échangé avec l'autre client pour créer le lien entre les deux.
    } catch (EncodeError &e) {
        throw FatalError("FatalError (Encode): ", e.what());
    } catch (AudioIOError &e) {
        throw FatalError("FatalError (AudioIO): ", e.what());
    } catch (std::exception &e) {
        throw FatalError("Fatal Error: ", e.what());
    }
}
