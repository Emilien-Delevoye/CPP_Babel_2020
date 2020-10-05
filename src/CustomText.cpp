/*!
 * @file CustomText.cpp
 * @brief CustomText class implementation
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 *
*/

#include "CustomText.hpp"

/*!
 * \brief The constructor of CustomText inherit of the QLabel class.
 * \param parent Parent widget (default value set to : nullptr)
 *
 * \param text text to be set
 *
*/

CustomText::CustomText(QWidget *parent, const QString &text) : QLabel(parent)
{
    setText(text);
}