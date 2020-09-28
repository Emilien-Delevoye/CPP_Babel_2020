/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Audio/PortAudio.hpp"
#include "Audio/Opus.hpp"
#include "Network/NetworkUDP.hpp"
#include <iostream>

void audioDemo()
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
}

int main(int argc, char **argv)
{
    if (argc == 1)
        NetworkUDP udp("127.0.0.1", 4242, true);
    else
        NetworkUDP udp("127.0.0.1", 4242, false);
    return 0;
}