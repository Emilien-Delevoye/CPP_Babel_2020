/*!
 * @file CustomWidget.cpp
 * @brief CustomWidget class implementation
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 *
*/

#include "CustomWidget.hpp"

/*!
 * \brief The constructor of CustomWidget inherit of the QWidget class.
 * \param parent Parent widget (default value set to : nullptr)
 *
*/

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{

}

/*!
 * \brief This method overridden from QWidget permit to customise the CustomWidget color.
 * \param event A QPaintEvent which determine that the CustomWidget can be customised.
 *
 * Without this method, the CustomWidget cannot be customised.
*/

void CustomWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}