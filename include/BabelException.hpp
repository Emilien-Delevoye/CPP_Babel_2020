/*!
 * @file BabelException.hpp
 * @brief BabelExceptionclass prototype
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 *
 * This class permit to deal with Babel error.
 *
*/

#ifndef BABEL_BABELEXCEPTION_HPP
#define BABEL_BABELEXCEPTION_HPP

#include <exception>
#include <string>

class BabelException : public std::exception
{
    public:
        explicit BabelException(std::string component = "Component: ",
                                std::string message = "An error occured.") : _component(std::move(component)), _message(std::move(message)) {};

        std::string const &getComponent() const { return this->_component; };
        const char* what() const noexcept override {
            return this->_message.c_str();
        };

    private:
        std::string _component;
        std::string _message;
};

class OpusError : public BabelException
{
    public:
        explicit OpusError(std::string const &component = "Opus: ",
                          std::string const &message = "An error occurred.") : BabelException(component, message) {};
};

class PortaudioError : public BabelException
{
public:
    explicit PortaudioError(std::string const &component = "Portaudio: ",
                            std::string const &message = "An error occurred.") : BabelException(component, message) {};
};

#endif //BABEL_BABELEXCEPTION_HPP
