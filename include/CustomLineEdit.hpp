/*!
 * @file CustomLineEdit.hpp
 * @brief CustomLineEdit class prototype
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 * This class permit to create custom line edit inherited from QLineEdit.
 * You can easily get the Text from the line edit thanks to the text() method of QLineEdit.
*/


#ifndef BABEL_CUSTOMLINEEDIT_HPP
#define BABEL_CUSTOMLINEEDIT_HPP

#include <QLineEdit>

class CustomLineEdit : public QLineEdit {
    Q_OBJECT
    public:
        explicit CustomLineEdit(QWidget *parent = nullptr);
};

#endif //BABEL_CUSTOMLINEEDIT_HPP
