/*!
 * @file UserPage.hpp
 * @brief UserPage class prototype
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 * This class represent the user page (visible once the user is connected).<br>
 * This class permit the connection with another user connected to the same server.<br>
 * YThe user can go back to the connection page thanks to the logout button.
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
#include <QScrollArea>
#include <QTimer>
#include <QTime>
#include "CustomLineEdit.hpp"
#include "CustomButton.hpp"
#include "CustomWidget.hpp"
#include "CustomText.hpp"
#include "enum.hpp"
#include "User.hpp"

class UserPage : public CustomWidget {
    Q_OBJECT
    public:
        explicit UserPage(QWidget *parent = nullptr);
        CustomButton *getLogOutButton() const;
        void init(const std::string &serverIP, const std::string &userLogin);
        CustomButton *getHangUpButton() const;
        CustomButton *getCallButton() const;
        CustomButton *getPickUpButton() const;
        void setUserInfo(const std::string &login, const std::string &ip);
        void showTimer();
        void hideTimer();
        void addUser(User *user);
        void deleteUser(int id, int otherUserId);
        void deleteAllUser();
        bool userExists(int id);
        std::vector<User *> getUsers() {return _users;}
        void incomingCall(int id);
        User *findUser(int id);
        void endcomingCall(const int id);

    private:
        std::vector<User *> _users;
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
        CustomButton *_pickUpButton;
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
