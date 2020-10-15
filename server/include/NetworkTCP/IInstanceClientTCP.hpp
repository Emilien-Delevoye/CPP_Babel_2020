/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Cyprien
*/


#ifndef BABEL_IINSTANCECLIENTTCP_HPP
#define BABEL_IINSTANCECLIENTTCP_HPP

class IInstanceClientTCP {
protected:
    IInstanceClientTCP() = default;

    virtual void startAsyncRead() = 0;
    virtual void write(std::string &) = 0;
    virtual std::string getData() const = 0;
    virtual std::string getDataClear() = 0;
    virtual void clearReceivedData() = 0;
    virtual int getId() const = 0;
    virtual bool isDisconnected() const = 0;
    virtual std::string getIp() const = 0;
};

#endif //BABEL_IINSTANCECLIENTTCP_HPP
