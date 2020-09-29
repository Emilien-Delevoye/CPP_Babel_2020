//
// Created by paul on 9/28/20.
//

#ifndef BABEL_ENUM_HPP
#define BABEL_ENUM_HPP

enum QtButtonsID {
    HOME_CONNECT_BUTTON
};

enum QtFormTextValues {
    HOME_IP_TEXT,
    HOME_LOGIN_TEXT,
    HOME_PASSWORD_TEXT
};

const std::vector<QString> formValue = {"IP &server :", "&Login :", "&Password :"};

enum QtLineEditID {
    HOME_IP_LINE_EDIT,
    HOME_LOGIN_LINE_EDIT,
    HOME_PASSWORD_LINE_EDIT
};
#endif //BABEL_ENUM_HPP
