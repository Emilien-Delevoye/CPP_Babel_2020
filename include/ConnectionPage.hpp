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
#include "CustomText.hpp"
#include "CustomWidget.hpp"
#include "enum.hpp"


class ConnectionPage : public CustomWidget {
    Q_OBJECT
    public:
        explicit ConnectionPage(QWidget *parent = nullptr);
        CustomButton *getConnectButton() const;
        void init();
        void fillUserInfo(std::string &serverIp, std::string &userLogin, std::string &userPassword) const;
        void emptyPassword();
        void setError(const std::string &errorMessage);
    private:
        CustomButton *_connectButton;
        QMap<QtLineEditID, CustomLineEdit *> _lineEdits;
        QVBoxLayout *_vLayout;
        QFormLayout *_formLayout;
        CustomWidget *_formWidget;
        CustomText *_errorMessage;
};

#endif //BABEL_CONNECTIONPAGE_HPP
