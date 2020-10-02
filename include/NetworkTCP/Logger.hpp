//
// Created by Cyprien on 02/10/2020.
//

#ifndef BABEL_LOGGER_HPP
#define BABEL_LOGGER_HPP


#include <string>
#include <iostream>

namespace Logger {
    enum State {
        SUCCESS,
        FAILURE,
        ERROR,
        FATAL_ERROR,
        INFO
    };
    void Log(std::string msg, State state)
    {
        std::cout << msg << std::endl << std::flush;
    }
}

#endif //BABEL_LOGGER_HPP
