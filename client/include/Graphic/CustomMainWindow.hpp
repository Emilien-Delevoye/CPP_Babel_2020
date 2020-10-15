/*!
 * @file CustomMainWindow.hpp
 * @brief CustomMainWindow class prototype
 * @authors Paul.S Cyprien.R
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
#include "Graphic/ConnectionPage.hpp"
#include "UserPage.hpp"
#include "enum.hpp"
#include "ClientTcp.hpp"
#include "Call.hpp"

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
    void startServerBackCall();
    void ConnectNLogToServer();
    void setupClients(const Communication &msg);
    void logout();
    void hangUp();
    void pickUpPressed();
    void call();
    void connectButtons();
    void connectionAccepted(const Communication &msg);
    void connectionRefused();
    void pickUpMsgReceived();
    void hangUpMsgReceived(const Communication &msg);
    void CallMessageReceived(const Communication &msg);
    void setupCallBacks(const Communication &msg);
    void startCall(const std::string &, int portReceiver, int portSender);

    ConnectionPage *_connectionPage;
    UserPage *_userPage;
    QStackedWidget *_pages;

    int _otherId;
    std::string _otherIP;
    std::string _otherLogin;
    int _otherPort = -1;

    std::string _serverIP;
    std::string _serverPort;

    int _userId;
    std::string _userLogin;
    std::string _userPassword;
    bool _callInProgress;

    ClientTCP *_serverTCP = nullptr;
    Communication _com;

    QTimer *_timer;
    Call *_call = nullptr;
    std::thread *_q = nullptr;
};

#endif //B_CPP_500_LIL_5_1_BABEL_CYPRIEN_RICQUE_QTMAINWINDOW_H
