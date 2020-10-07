/*!
 * @file ConnectionPage.hpp
 * @brief ConnectionPage class prototype
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 * This class represent the connection page (first page seeing by the user).<br>
 * This class permit the connection to the server thanks to different fields.<br>
 * Once connected, the user will navigate to the UserPage.
 *
*/

#ifndef BABEL_CONNECTIONPAGE_HPP
#define BABEL_CONNECTIONPAGE_HPP

#include <QVBoxLayout>
#include <QFormLayout>
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
