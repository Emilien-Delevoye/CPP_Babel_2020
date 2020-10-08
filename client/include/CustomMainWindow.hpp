/*!
 * @file CustomMainWindow.hpp
 * @brief CustomMainWindow class prototype
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 * This class permit to create the main window of your application.<br>
 * This class inherit from QMainWindow.<br>
 * This class inherit from QMainWindow.
*/

#ifndef B_CPP_500_LIL_5_1_BABEL_CYPRIEN_RICQUE_QTMAINWINDOW_H
#define B_CPP_500_LIL_5_1_BABEL_CYPRIEN_RICQUE_QTMAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QStackedWidget>
#include "CustomButton.hpp"
#include "CustomText.hpp"
#include "CustomLineEdit.hpp"
#include "ConnectionPage.hpp"
#include "UserPage.hpp"
#include "enum.hpp"
#include "ClientTcp.hpp"

class CustomMainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit CustomMainWindow(QWidget *parent = nullptr, const QString &title = "Babel");
    void navToUserPage();
    void navToConnectionPage();
    bool checkField() const;

private:
    void newUser(const Communication &msg);
    void newUser(User *user);

    ConnectionPage *_connectionPage;
    UserPage *_userPage;
    QStackedWidget *_pages;

    int _otherId;
    std::string _otherIP;
    std::string _otherLogin;

    std::string _serverIP;
    std::string _serverPort;

    int _userId;
    std::string _userLogin;
    std::string _userPassword;
    bool _callInProgress;

    ClientTCP _serverTCP;
    Communication _com;

    QTimer *_timer;

    void startServerBackCall();

    void ConnectLogToServer();

    void setupClients(const Communication &msg);
};

#endif //B_CPP_500_LIL_5_1_BABEL_CYPRIEN_RICQUE_QTMAINWINDOW_H
