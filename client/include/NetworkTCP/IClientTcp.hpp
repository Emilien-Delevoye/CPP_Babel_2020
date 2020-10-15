/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/


#ifndef BABEL_ICLIENTTCP_HPP
#define BABEL_ICLIENTTCP_HPP


class IClientTCP {
public:
    IClientTCP() = default;

    virtual bool connect(const std::string& ip, const std::string& port) = 0;
    virtual void startAsyncRead() = 0;

    virtual std::string read() = 0;
    virtual void async_read() = 0;
    virtual void write(std::string msg) = 0;
    virtual void async_write(std::string) = 0;

    virtual void disconnectThread() = 0;;
    virtual void disconnect() = 0;;

    virtual std::string getData() const = 0;
    virtual std::string getDataClear() = 0;
    virtual void clearReceivedData() = 0;
    virtual bool isDisconnected() const = 0;
    virtual void resetIsDisconnected() = 0;
};


#endif //BABEL_ICLIENTTCP_HPP
