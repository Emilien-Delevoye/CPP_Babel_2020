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

#ifdef _WIN32
    #define _WIN32_WINNT  0x0601
#endif

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

class FatalError : public BabelException
{
public:
    explicit FatalError(std::string const &component = "Fatal Error: ",
                        std::string const &message = "A fatal error occured.") : BabelException(component, message) {};
};

class EncodeError : public BabelException
{
    public:
        explicit EncodeError(std::string const &component = "Encode: ",
                          std::string const &message = "An error occurred.") : BabelException(component, message) {};
};

class AudioIOError : public BabelException
{
public:
    explicit AudioIOError(std::string const &component = "Portaudio: ",
                            std::string const &message = "An error occurred.") : BabelException(component, message) {};
};

class ServerError : public BabelException
{
public:
    explicit ServerError(std::string const &component = "Server: ",
            std::string const &message = "An error occurred.") : BabelException(component, message) {};

};

#endif //BABEL_BABELEXCEPTION_HPP
