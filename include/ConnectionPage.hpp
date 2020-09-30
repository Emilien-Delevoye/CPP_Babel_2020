/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#ifndef BABEL_CONNECTIONPAGE_HPP
#define BABEL_CONNECTIONPAGE_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include "CustomLineEdit.hpp"
#include "CustomButton.hpp"
#include "enum.hpp"


class ConnectionPage : public QWidget {
    public:
        ConnectionPage(QWidget *parent = nullptr);
        ~ConnectionPage();
        CustomButton *getConnectButton() const;
    private:
        CustomButton *_connectButton;
        QMap<QtLineEditID, CustomLineEdit *> _lineEdits;
        QVBoxLayout *_vLayout;
        QFormLayout *_formLayout;
        QWidget *_formWidget;
};

#endif //BABEL_CONNECTIONPAGE_HPP
