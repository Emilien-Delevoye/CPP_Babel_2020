/*!
 * @file Audio/AudioIO.hpp
 * @brief AudioIO class
 * @author Emilien.D
 * @version 1.0
 * @date 08/10/2020
 *
 * The AudioIO hpp file describes the override from IAudio and local PortAudio variables.
*/

#ifndef BABEL_AUDIOIO_HPP
#define BABEL_AUDIOIO_HPP

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

#include <vector>
#include <string>
#include "portaudio.h"
#include "IAudio.hpp"
#include "BabelException.hpp"

class AudioIO: public IAudio {
public:
    AudioIO();
    void init() final;
    void startStream(int, int) final;
    void readStream() override;
    void writeStream() override;
    void stopStream() final;
    [[nodiscard]] std::vector<unsigned short> getCaptured() const;
    void setDecoded(const std::vector<unsigned short> &);
    ~AudioIO();
private:
    void stop() final;
    enum _st {
            INPUT = 0,
            OUTPUT = 1
        };
    PaStreamParameters _portAudioParameters[2];
    const PaDeviceInfo* _deviceInfo[2];
    PaStream *_streamInput = nullptr;
    PaStream *_streamOutput = nullptr;
    std::vector<unsigned short> _captured;
    std::vector<unsigned short> _decoded;
    int _numChannels[2];
    bool _init = false;
    bool _fatalError = false;
};

#endif //BABEL_AUDIOIO_HPP
