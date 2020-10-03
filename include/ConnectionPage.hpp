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
#include <QStyleOption>
#include <QPainter>
#include "CustomLineEdit.hpp"
#include "CustomButton.hpp"
#include "enum.hpp"


class ConnectionPage : public QWidget {
    Q_OBJECT
    public:
        ConnectionPage(QWidget *parent = nullptr);
        ~ConnectionPage();
        void paintEvent(QPaintEvent *event) override;
        CustomButton *getConnectButton() const;
        void init();
        void fillUserInfo(std::string &userLogin, std::string &userIp) const;
        void emptyPassword();
    private:
        CustomButton *_connectButton;
        QMap<QtLineEditID, CustomLineEdit *> _lineEdits;
        QVBoxLayout *_vLayout;
        QFormLayout *_formLayout;
        QWidget *_formWidget;
};

#endif //BABEL_CONNECTIONPAGE_HPP
