/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/

#include "Call.hpp"
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
    /*try {
        audioDemo();
    } catch (OpusError &e) {
        std::cerr << e.what() << std::endl;
    } catch (PortaudioError &e) {
        std::cerr << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }*/
    Call call("127.0.0.1", 4242, true);
    return 0;
}