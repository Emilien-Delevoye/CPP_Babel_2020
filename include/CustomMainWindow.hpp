/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#ifndef B_CPP_500_LIL_5_1_BABEL_CYPRIEN_RICQUE_QTMAINWINDOW_H
#define B_CPP_500_LIL_5_1_BABEL_CYPRIEN_RICQUE_QTMAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QDebug>
#include <QFile>
#include <QStackedWidget>
#include "CustomButton.hpp"
#include "CustomText.hpp"
#include "CustomLineEdit.hpp"
#include "ConnectionPage.hpp"
#include "UserPage.hpp"
#include "enum.hpp"

class CustomMainWindow : public QMainWindow {
    Q_OBJECT
    public:
        explicit CustomMainWindow(QWidget *parent = nullptr, const QString &title = "Window");
        ~CustomMainWindow();
        void centered();
    private:
        ConnectionPage *_connectionPage;
        UserPage *_userPage;
        std::vector<User *> _users;
        QStackedWidget *_pages;
        std::string _ipToCall;
        std::string _loginToCall;
        void navToUserPage();
        void navToConnectionPage();

};

#endif //B_CPP_500_LIL_5_1_BABEL_CYPRIEN_RICQUE_QTMAINWINDOW_H
