/*!
 * @file CustomButton.hpp
 * @brief CustomButton class prototype
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 * This class permit to create custom button inherited from QPushButton.
 * To call a function when the CustomButton is clicked, you have to use the connect method from QT (see: CustomMainWindow).
 *
*/

#ifndef BABEL_CUSTOMBUTTON_HPP
#define BABEL_CUSTOMBUTTON_HPP

#include <QPushButton>

class CustomButton : public QPushButton {
    Q_OBJECT
    public:
        explicit CustomButton(QWidget *parent = nullptr, const QString &text = "text");
};

#endif //BABEL_CUSTOMBUTTON_HPP
