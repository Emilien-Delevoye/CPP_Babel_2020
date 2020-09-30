/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Paul
*/

#include "UserPage.hpp"

UserPage::UserPage(QWidget *parent) : QWidget(parent)
{
    _button = new QPushButton("Caca", this);
    hide();
}

UserPage::~UserPage()
{

}