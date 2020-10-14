/*!
 * @file Audio/IAudio.hpp
 * @brief IAudio interface
 * @author Emilien.D
 * @version 1.0
 * @date 08/10/2020
 *
 * The IAudio interface describes the methods and constants for the AudioIO class
*/

#ifndef BABEL_IAUDIO_HPP
#define BABEL_IAUDIO_HPP

class IAudio {
    public:
        virtual void init() = 0;
        virtual void startStream(int, int) = 0;
        virtual void readStream() = 0;
        virtual void writeStream() = 0;
        virtual void stopStream() = 0;
        virtual void stop() = 0;
    protected:
        //channel and sample data
        const int CHANNEL_NB = 2;
        //Frames data
        const int SAMPLE_RATE = 48000;
        const int FRAME_SIZE = 120;
};

#endif //BABEL_IAUDIO_HPP
