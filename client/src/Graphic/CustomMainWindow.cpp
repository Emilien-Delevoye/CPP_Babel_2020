/*!
 * @file CustomMainWindow.cpp
 * @brief CustomMainWindow class implementation
 * @authors Paul.S Cyprien.R Emilien.D
 * @version 1.0
 * @date 05/10/2020
 *
*/

#include "Graphic/CustomMainWindow.hpp"

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

    connectButtons();

    _pages->addWidget(_userPage);
    _pages->addWidget(_connectionPage);
    setCentralWidget(_pages);
    navToConnectionPage();
}

/*!
 * \brief CustomMainWindow constructor

 * This method connects the buttons to their actions.
*/

void CustomMainWindow::connectButtons()
{
    connect(_connectionPage->getConnectButton(), &QPushButton::clicked, [=]() {
        _connectionPage->fillUserInfo(_serverIP, _serverPort, _userLogin, _userPassword);
        if (checkField())
            ConnectNLogToServer();
    });
    connect(_userPage->getLogOutButton(), &QPushButton::clicked, [=]() {
        if (!_callInProgress)
            logout();
    });
    connect(_userPage->getCallButton(), &QPushButton::clicked, [=]() { call();});
    connect(_userPage->getHangUpButton(), &QPushButton::clicked, [=]() {
        _serverTCP->async_write(Communication::serializeObj(Communication(Communication::HANG_UP, _userId, _otherId, 4241)));
        if (_callInProgress)
            hangUp();
    });
    connect(_userPage->getPickUpButton(), &QPushButton::clicked, [=]() { pickUpPressed();});
}

/*!
 * \brief call method
 *
 * Actions when call button is pressed
*/

void CustomMainWindow::call()
{
    std::cout << "CALL PASSED " << _otherId << std::endl;
    _serverTCP->async_write(Communication(Communication::CALL, _userId, _otherId, 4242).serialize());
    _callInProgress = true;
    _userPage->getCallButton()->hide();
    _userPage->getHangUpButton()->show();
}

/*!
 * \brief pickUpPressed method
 *
 * Actions when pickUp button is pressed
*/

void CustomMainWindow::pickUpPressed()
{
    _serverTCP->async_write(Communication::serializeObj(Communication(Communication::PICK_UP, _userId, _otherId, 4241)));
    startCall(_otherIP, 4241, 4242);
    if (_call)
        _q = new(std::nothrow) std::thread([&] { _call->run(); });
    _callInProgress = true;
    _userPage->showTimer();
    _userPage->getPickUpButton()->hide();
    _userPage->getHangUpButton()->show();
}

/*!
 * \brief hangUp method
 *
 * this method hang up the client when the button is pressed or the message is received.
*/

void CustomMainWindow::hangUp()
{
    if (_call && _q) {
        std::cout << "stop Call" << std::endl;
        _call->stopCall();
        delete _call;
        _call = nullptr;
        _q->join();
        std::cout << "stop Call ok" << std::endl;
    }
    _callInProgress = false;
    _userPage->endcomingCall(_otherId);
}

/*!
 * \brief logout method
 *
 * this method logout the client from the server.
*/

void CustomMainWindow::logout()
{
    _serverTCP->resetIsDisconnected();
    _serverTCP->disconnectThread();
    _connectionPage->emptyPassword();
    if (_callInProgress) {
        std::cout << "Automatic call in progress" << std::endl;
        hangUp();
    }
    _callInProgress = false;
    navToConnectionPage();
    _timer->stop();
}

/*!
 * \brief connectLogToServer method
 *
 * This method allow the client to connect himself and log to the server.
 * The client is logged with the password and login entered in the window.
*/

void CustomMainWindow::ConnectNLogToServer()
{
    _serverTCP = new ClientTCP;
    Communication msg(Communication::HANG_UP);

    if (_serverTCP->connect(_serverIP, _serverPort)) {
        _serverTCP->write(Communication(Communication::PRESENTATION, _userLogin, _userPassword, 4242).serialize());
        try {
            msg = Communication::unSerializeObj(std::string(_serverTCP->read()));
        } catch (boost::system::system_error &e) {
            std::cerr << "Get answer Error " << e.what() << std::endl;
            msg.connectionAccepted = false;
        }
        if (msg.connectionAccepted)
            connectionAccepted(msg);
        else
            connectionRefused();
    } else {
        _connectionPage->setError("Error while connecting to the server.");
        delete _serverTCP;
        _serverTCP = nullptr;
    }
}

/*!
 * \brief connectionRefused method
 *
 * Actions when the connection to the server is refused
*/

void CustomMainWindow::connectionRefused()
{
    _connectionPage->setError("Invalid password or User already connected");
    _serverTCP->disconnect();
    delete _serverTCP;
    _serverTCP = nullptr;
}

/*!
 * \brief connectionAccepted method
 *
 * Actions when the connection to the server is accepted
*/

void CustomMainWindow::connectionAccepted(const Communication &msg)
{
    _userId = msg.id_;
    setupClients(msg);
    startServerBackCall();
    navToUserPage();
    qDebug() << "Connected as" << qPrintable(_userLogin.c_str()) << "with Password" << qPrintable(_userPassword.c_str()) << endl;
}

/*!
 * \brief startServerBackCall method
 *
 * this method start the regular call back to the server.
*/

void CustomMainWindow::startServerBackCall()
{
    _serverTCP->clearReceivedData();
    _serverTCP->startAsyncRead();
    _timer = new QTimer(this);
    _timer->setInterval(300);

    connect(_timer, &QTimer::timeout, [&]() {
        if (_serverTCP && _serverTCP->isDisconnected())
            logout();
        if (_serverTCP->getData().empty())
            return;
        std::cout << "Message received !" << std::endl; // DEBUG
        auto msg = Communication::unSerializeObj(_serverTCP->getDataClear());

        setupCallBacks(msg);
    });
    _timer->start();
}

/*!
 * \brief setupCallBacks method
 * \param Communication msg
 *
 * setup call back when a message is received from server
*/

void CustomMainWindow::setupCallBacks(const Communication &msg)
{
    if (msg.t_ == Communication::DISCONNECTED_USER) {
        qDebug() << "DISCONNECTED USER RCV" << endl;
        _userPage->deleteUser(msg.id_, _otherId);
    } else if (msg.t_ == Communication::PICK_UP) {
        pickUpMsgReceived();
    } else if (msg.t_ == Communication::CALL) {
        CallMessageReceived(msg);
    } else if (msg.t_ == Communication::HANG_UP) {
        hangUpMsgReceived(msg);
    } else if (msg.t_ == Communication::SETUP) {
        setupClients(msg);
    } else {
        qDebug() << "UNKNOWN MESSAGE TYPE" << endl;
    }
}

/*!
 * \brief CallMessageReceived method
 *
 * Actions when call msg received
*/

void CustomMainWindow::CallMessageReceived(const Communication &msg)
{
    qDebug() << "CALL RCV" << endl;
    std::cout << "CALL RECEIVED " << msg.id_ << std::endl;
    if (_callInProgress) {
        _serverTCP->async_write(Communication::serializeObj(
                Communication(Communication::HANG_UP, _userId, msg.id_, 4241)));
    } else {
        _callInProgress = true;
        _otherId = _userPage->findUser(msg.id_)->getID();
        _otherLogin = _userPage->findUser(msg.id_)->getLogin();
        _otherIP = _userPage->findUser(msg.id_)->getIP();
        _otherPort = msg.port_;
        _userPage->incomingCall(msg.id_);
    }
}

/*!
 * \brief hangUpMsgReceived method
 *
 * Actions when the "hang up" Msg is received
*/

void CustomMainWindow::hangUpMsgReceived(const Communication &msg)
{
    qDebug() << "HANG UP RCV" << endl;
    if (msg.id_ == _otherId) {
        _callInProgress = false;
        _userPage->endcomingCall(msg.id_);
        if (_call && _q) {
            std::cout << "stop Call (button)" << std::endl;
            _call->stopCall();
            delete _call;
            _call = nullptr;
            _q->join();
            std::cout << "stop Call (button) ok" << std::endl;
        }
    }
}

/*!
 * \brief pickUpMsgReceived method
 *
 * Actions when the "pick up" Msg is received
*/

void CustomMainWindow::pickUpMsgReceived()
{
    _userPage->showTimer();
    startCall(_otherIP, 4242, 4241);
    if (_call)
        _q = new(std::nothrow) std::thread([&] { _call->run(); });
    _callInProgress = true;
}

/*!
 * \brief setupClients method
 * \param Communication message (message received from server)
 *
 * This method add connected clients to the UI when "SETUP" message is received.
*/

void CustomMainWindow::setupClients(const Communication &msg)
{
    for (int i = 0; i < msg.ids_.size(); ++i)
        if ((!_userPage->userExists(msg.ids_.at(i))) && (msg.ids_.at(i) != _userId))
            newUser(new User(_userPage, msg.logins_.at(i), msg.ips_.at(i), msg.ports_.at(i),
                             msg.ids_.at(i)));
    auto users = _userPage->getUsers();
    for (auto &u : users)
        if (std::find(msg.ids_.begin(), msg.ids_.end(), u->getID()) == msg.ids_.end())
            _userPage->deleteUser(u->getID(), _otherId);
}

/*!
 * \brief newUser method
 * \param Communication message (message received)
 *
 * this method permit the client to add new connected users to the UI from a received message.
*/

void CustomMainWindow::newUser(const Communication &msg)
{
    newUser(new User(_userPage, msg.login_, msg.ip_, msg.port_, msg.id_));
}

/*!
 * \brief newUser method
 * \param User user
 *
 * this method permit the client to add new connected users to the UI.
*/

void CustomMainWindow::newUser(User *user)
{
    user->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    std::string tooltip = std::string("Display information about ") + std::string(user->getLogin());
    user->setToolTip(tooltip.c_str());
    user->setMinimumHeight(50);
    connect(user, &QPushButton::clicked, [=]() {
        if (!_callInProgress) {
            _otherIP = user->getIP();
            _otherLogin = user->getLogin();
            _otherId = user->getID();
            _userPage->setUserInfo(_otherLogin, _otherIP);
        }
    });
    _userPage->addUser(user);
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

/*!
 * \brief startCall method
 * \param std::string in
 * \param int portReceiver
 * \param int portSender
 *
 * This method start the UDP call.<br>
*/

void CustomMainWindow::startCall(const std::string &in, int portReceiver, int portSender)
{
    try {
        _call = new(std::nothrow) Call(in, portReceiver, portSender);
    } catch (EncodeError &e) {
        std::cerr << e.getComponent() << e.what() << std::endl;
    } catch (AudioIOError &e) {
        std::cerr << e.getComponent() << e.what() << std::endl;
    } catch (FatalError &e) {
        std::cerr << e.getComponent() << e.what() << std::endl;
    } catch (boost::system::system_error &e) {
        std::cerr << "Boost system error : " << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Call init error : " << e.what() << std::endl;
    }
}
