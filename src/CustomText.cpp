/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#include <CustomText.hpp>

#include "CustomText.hpp"

CustomText::CustomText(QWidget *parent, const QString &text) : QLabel(parent)
{
    setText(text);
}