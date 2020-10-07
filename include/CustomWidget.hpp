/*!
 * @file CustomWidget.hpp
 * @brief CustomWidget class prototype
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 * This class permit to create customisable widget.
 *
*/

#ifndef BABEL_CUSTOMWIDGET_HPP
#define BABEL_CUSTOMWIDGET_HPP

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QObject>

class CustomWidget : public QWidget {
    Q_OBJECT
    public:
        explicit CustomWidget(QWidget *parent = nullptr);
        void paintEvent(QPaintEvent *event) override;
    private:


};

#endif //BABEL_CUSTOMWIDGET_HPP
