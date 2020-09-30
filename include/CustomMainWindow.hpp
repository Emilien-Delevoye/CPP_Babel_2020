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
#include "CustomButton.hpp"
#include "CustomText.hpp"
#include "CustomLineEdit.hpp"
#include "ConnectionPage.hpp"
#include "UserPage.hpp"
#include "enum.hpp"

class CustomMainWindow : public QMainWindow {
    Q_OBJECT
    public:
        void centered();
        explicit CustomMainWindow(QWidget *parent = nullptr, const QString &title = "Window");
        void test();
        ~CustomMainWindow();
    private slots:
        void navToUserPage();
    private:
        ConnectionPage *_connectionPage;
        UserPage *_userPage;
};

#endif //B_CPP_500_LIL_5_1_BABEL_CYPRIEN_RICQUE_QTMAINWINDOW_H
