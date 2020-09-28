/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#include "CustomButton.hpp"

CustomButton::CustomButton(QWidget *parent, const QString &title) : QPushButton(parent)
{
    setText(title);
}

CustomButton::~CustomButton()
{

}


