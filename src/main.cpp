/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/


#include "QT.hpp"
#include "QTMainWindow.hpp"
#include "CustomButton.hpp"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    QTMainWindow w(nullptr, "Babel");

    CustomButton toto(&w, "toto");

    w.show();

    return a.exec();
}
