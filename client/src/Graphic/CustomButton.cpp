/*!
 * @file CustomButton.cpp
 * @brief CustomButton class implementation
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
*/

#include "Graphic/CustomButton.hpp"

/*!
 * \brief CustomButton constructor
 * \param parent parent widget (default value set to : nullptr)
 * \param text button text
 *
 * This method permit to set the button Text and the cursor type when the button is hovered.
*/

CustomButton::CustomButton(QWidget *parent, const QString &text) : QPushButton(parent)
{
    setText(text);
    setCursor(Qt::PointingHandCursor);
}

