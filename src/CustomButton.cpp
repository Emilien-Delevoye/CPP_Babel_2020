/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#include "CustomButton.hpp"

CustomButton::CustomButton(QWidget *parent, const QString &text) : QPushButton(parent)
{
    setText(text);
    setCursor(Qt::PointingHandCursor);
}


