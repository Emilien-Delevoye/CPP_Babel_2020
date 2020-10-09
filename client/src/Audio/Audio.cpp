/*!
 * @file Audio/Audio.cpp
 * @brief Audio class
 * @author Emilien.D
 * @version 1.0
 * @date 08/10/2020
 *
 * The Audio class heirs from Encode and AudioIO
 * This class aggregates the Input Audio read, the Output Audio write and the encoding/decoding
 * The pointer to the object created is send to the NetworkUDP class
*/

#include "Audio/Audio.hpp"
#include <iostream>

/*!
* \brief Audio constructor init Encode and AudioIO objects and init encoder, decoder and streams
*/

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
