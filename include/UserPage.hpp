//
// Created by paul on 9/29/20.
//

#ifndef BABEL_USERPAGE_HPP
#define BABEL_USERPAGE_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include "CustomLineEdit.hpp"
#include "CustomButton.hpp"
#include "enum.hpp"


class UserPage : public QWidget {
    public:
        UserPage(QWidget *parent = nullptr);
        ~UserPage();
    private:
        QPushButton *_button;
};

#endif //BABEL_USERPAGE_HPP
