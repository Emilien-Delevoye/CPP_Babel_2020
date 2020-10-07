/*!
 * @file CustomMainWindow.cpp
 * @brief CustomMainWindow class implementation
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 *
*/

#include "CustomMainWindow.hpp"

/*!
 * \brief CustomMainWindow constructor
 * \param parent parent widget (default value set to : nullptr)
 * \param title window's title
 * This constructor inherit from QMainWindow and permit to create the pages and establish some button's connection thanks to Qt "connect" method.
*/

CustomMainWindow::CustomMainWindow(QWidget *parent, const QString &title) : QMainWindow(parent)
{
    setWindowTitle(title);

    _connectionPage = new ConnectionPage(this);
    _userPage = new UserPage(this);
    _pages = new QStackedWidget(this);

    _callInProgress = false;

    connect(_connectionPage->getConnectButton(), &QPushButton::clicked, [=]() {
        _connectionPage->fillUserInfo(_serverIP, _serverPort, _userLogin, _userPassword);
        if (checkField()) {
            qDebug() << qPrintable(_serverIP.data()) << ", " << qPrintable(_serverPort.data()) << endl;
            _serverTCP.connect(_serverIP, _serverPort);
            navToUserPage();
            qDebug() << "Connected as " << qPrintable(_userLogin.c_str()) << " with Ip address " << qPrintable(_userLogin.c_str()) << endl;
        }
    });
    connect(_userPage->getLogOutButton(), &QPushButton::clicked, [=]() {
        if (!_callInProgress) {
            _connectionPage->emptyPassword();
            navToConnectionPage();
        }
    });
    connect(_userPage->getCallButton(), &QPushButton::clicked, [=]() {
        _serverTCP.async_write(Communication::serializeObj(Communication(Communication::CALL, _otherId)));
        _callInProgress = true;
        _userPage->showTimer();
        _userPage->getCallButton()->hide();
        _userPage->getHangUpButton()->show();
    });
    connect(_userPage->getHangUpButton(), &QPushButton::clicked, [=]() {
        _serverTCP.async_write(Communication::serializeObj(Communication(Communication::HANG_UP, _otherId)));
        _callInProgress = false;
        _userPage->hideTimer();
        _userPage->getHangUpButton()->hide();
        _userPage->getCallButton()->show();
    });
    _pages->addWidget(_userPage);
    _pages->addWidget(_connectionPage);

    setCentralWidget(_pages);
    navToConnectionPage();

    _timer = new QTimer(this);
    _timer->setInterval(1000);
    connect(_timer, &QTimer::timeout, [&]() {
        std::string dt = _serverTCP.getDataClear();
        std::cout << "rcv: " << dt << std::endl;
        /* create a new user */
        /*User *user;
        user = new User(_userPage, "Jean", std::string("127.0.0."), 4, 5);
        user->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        std::string tooltip = std::string("Display information about ") + std::string("Jean");
        user->setToolTip(tooltip.c_str());
        user->setMinimumHeight(50);
        connect(user, &QPushButton::clicked, [=]() {
            if (!_callInProgress) {
                _otherIP = user->getIP();
                _otherLogin = user->getLogin();
                _userPage->setUserInfo(_otherLogin, _otherIP);
            }
        });
        _userPage->addUser(user);*/

         // delete a  user with

        //_userPage->deleteUser(5);

        // delete all user

        //_userPage->deleteAllUser();
    });
    _timer->start();

}

/*!
 * \brief This method permit to navigate to the UserPage
 * The navigation happens after the user click on the "connect" button from the ConnectionPage (the fields have to be valid).<br>
 * Before navigation, this method create all the User Button and connect them to the callback represented by a anonymous function (lambda).<br>
 * Moreover, the  method is called, and then, the central widget is updated.
*/

void CustomMainWindow::navToUserPage()
{
    _userPage->init(_serverIP, _userLogin);
    _pages->setCurrentWidget(_userPage);
}

/*!
 * \brief This method permit to navigate to the ConnectionPage
 * The navigation happens after the user click on the button from the UserPage.<br>
 * Before navigation, this method delete all User Button in order to free some memory and clear _users vector.<br>
 * Moreover, the method is called, and then, the central widget is updated.
*/

void CustomMainWindow::navToConnectionPage()
{
    _connectionPage->init();
    _pages->setCurrentWidget(_connectionPage);
}

/*!
 * \brief This method permit to check the ConnectPage fields.
 * If on the field isn't correct or if the connection with the DB failed, an error message is showed to the user corresponding the the happening error.<br>
 * (example: "Error: Server field is empty)"
*/

bool CustomMainWindow::checkField() const
{
    if (_serverIP.empty()) {
        _connectionPage->setError("Error: Server field is empty.");
        return false;
    } else if (_serverPort.empty()) {
        _connectionPage->setError("Error: Port field is incorrect.");
        return false;
    } else if (_userLogin.empty()) {
        _connectionPage->setError("Error: Login field is empty.");
        return false;
    } else if (_userPassword.empty()) {
        _connectionPage->setError("Error: Password field is empty.");
        return false;
    }
    return true;
}
