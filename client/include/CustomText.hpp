/*!
 * @file CustomText.hpp
 * @brief CustomText class prototype
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 * This class permit to create customisable text.
 *
*/

#ifndef BABEL_CUSTOMTEXT_HPP
#define BABEL_CUSTOMTEXT_HPP

#include <QLabel>

class CustomText : public QLabel {
    Q_OBJECT
    public:
        explicit CustomText(QWidget *parent = nullptr, const QString &text = "text");
    private:

};

#endif //BABEL_CUSTOMTEXT_HPP
