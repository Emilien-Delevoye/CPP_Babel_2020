/*!
 * @file enum.hpp
 * @brief Graphic enum file
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 * This file contain all the enum which be used for the graphic view.
 *
*/

#ifndef BABEL_ENUM_HPP
#define BABEL_ENUM_HPP

enum QtButtonsID {
    HOME_CONNECT_BUTTON
};

enum QtFormTextValues {
    HOME_IP_TEXT,
    HOME_PORT_TEXT,
    HOME_LOGIN_TEXT,
    HOME_PASSWORD_TEXT
};

const std::vector<QString> formValue = {"Server IP :", "Server port :", "Login :", "Password :"};

enum QtLineEditID {
    HOME_IP_LINE_EDIT,
    HOME_PORT_LINE_EDIT,
    HOME_LOGIN_LINE_EDIT,
    HOME_PASSWORD_LINE_EDIT
};
#endif //BABEL_ENUM_HPP
