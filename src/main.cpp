/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "PortAudio.hpp"
#include "Opus.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    Opus opus;
    PortAudio portAudio;

    opus.createEncoder();
    opus.createDecoder();
    portAudio.startStream();
    for (int i = 0; i < ((3000 * 48000) / 512); ++i) {
        portAudio.readStream();
        opus.setCaptured(portAudio.getCaptured());
        opus.encodeData();
        opus.decodeData();
        portAudio.setDecoded(opus.getDecoded());
        portAudio.writeStream();
    }
    portAudio.stopStream();
    std::cout << "End stream" << std::endl;
    portAudio.~PortAudio();
    opus.~Opus();
    return 0;
}
