/*!
 * @file Audio/IAudio.hpp
 * @brief IAudio class
 * @author Emilien.D
 * @version 1.0
 * @date 08/10/2020
 *
 * The IAudio interface describes the methods and constants for the AudioIO class
*/
#ifndef BABEL_AUDIO_HPP
#define BABEL_AUDIO_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include "Encode.hpp"
#include "AudioIO.hpp"

class Audio : public Encode, public AudioIO {
public:
    explicit Audio();
};

#endif //BABEL_AUDIO_HPP
