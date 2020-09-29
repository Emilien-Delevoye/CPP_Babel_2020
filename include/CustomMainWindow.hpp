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

#include "CustomButton.hpp"
#include "CustomText.hpp"
#include "CustomLineEdit.hpp"
#include "enum.hpp"

class CustomMainWindow : public QMainWindow {
    public:
        CustomMainWindow(QWidget *parent = nullptr, const QString &title = "Window");
        ~CustomMainWindow();
    private:
        QPushButton *_connectButton;
        QMap<QtLineEditID, CustomLineEdit *> _lineEdits;
        QVBoxLayout *_vLayout;
        QFormLayout *_formLayout;
        QWidget *_mainWidget;

};

#endif //B_CPP_500_LIL_5_1_BABEL_CYPRIEN_RICQUE_QTMAINWINDOW_H
