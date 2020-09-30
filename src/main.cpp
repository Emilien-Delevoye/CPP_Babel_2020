/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Created by Emilien
*/


#include "CustomMainWindow.hpp"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    QFile File("../../styles/styles.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    a.setStyleSheet(StyleSheet);
    auto *babel = new CustomMainWindow(nullptr, "Babel");
    babel->show();
    return a.exec();
}
