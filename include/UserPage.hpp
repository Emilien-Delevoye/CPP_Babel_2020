/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#ifndef BABEL_USERPAGE_HPP
#define BABEL_USERPAGE_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <vector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QStyleOption>
#include <QPainter>
#include <QScrollArea>
#include <QTimer>
#include <QTime>
#include "CustomLineEdit.hpp"
#include "CustomButton.hpp"
#include "CustomWidget.hpp"
#include "CustomText.hpp"
#include "enum.hpp"
#include "User.hpp"

class UserPage : public QWidget {
    Q_OBJECT
    public:
        explicit UserPage(QWidget *parent = nullptr);
        ~UserPage();
        CustomButton *getLogOutButton() const;
        void paintEvent(QPaintEvent *event) override;
        void init(const std::vector<User *>& _users, const std::string &serverIP, const std::string &userLogin);
        CustomButton *getHangUpButton() const;
        CustomButton *getCallButton() const;
        void setUserInfo(const std::string &login, const std::string &ip);
        void showTimer();
        void hideTimer();
    private:
        QHBoxLayout *_hLayout;
        CustomWidget *_usersWidget;
        CustomWidget *_callWidget;
        CustomWidget *_callWidgetTop;
        CustomWidget *_callWidgetMiddle;
        CustomWidget *_callWidgetBottom;
        QScrollArea *_usersList;
        QVBoxLayout *_userVLayout;
        QVBoxLayout *_callVLayout;
        QVBoxLayout *_callVLayoutTop;
        QVBoxLayout *_callVLayoutMiddle;
        QHBoxLayout *_callHLayoutBottom;
        CustomButton *_callButton;
        CustomButton *_logOutButton;
        CustomText *_userLoginToCall;
        CustomText *_userIPToCall;
        CustomButton *_hangUpButton;
        QTimer *_timer;
        CustomText *_timerText;
        CustomText *_actualTime;
        int _elapsedSeconds;
        CustomText *_userConnectedText;
        CustomText *_serverIPText;


};

#endif //BABEL_USERPAGE_HPP
