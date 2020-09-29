/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/


#include "QT.hpp"
#include "CustomMainWindow.hpp"
#include "CustomButton.hpp"
#include <QObject>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    QT *babel = new QT();

    babel->getMainWindow()->show();
    return a.exec();
}
