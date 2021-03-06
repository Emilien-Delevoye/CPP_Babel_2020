/*! \mainpage Welcome to our Babel documentation !
 *
 * \section a About this documentation
 *
 * This documentation was first generated on 3/4/2020 thanks to Doxygen (https://www.doxygen.nl).
 * <br>
 * The purpose of this documentation is to give tools to any developer who wants add new features to our project (Babel).
 *
 * \section b Project Description
 *
 * The project consists in a client/server architecture voice over IP application, similar to Skype or TeamSpeak.
 * <br>
 * The Babel project aims to create an SIP-like Voice Over IP (VOIP) protocol. It MUST be usable over the
 * Internet (no multicast or anything LAN specific).
 *
 * \section c Install dependencies
 * To how to compile Babel, see the Readme.md (related pages -> babel)
 *
 * \authors Cyprien Ricque <br> Emilien Delevoye <br> Paul Surrans
*/

/*!
 * @file main.cpp
 * @brief Babel client initial file
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 *
 * The main file of the Babel client contains the main function.
 * It creates Babel application and set the relation with the styles.qss file to customise our application.
 * Moreover, it creates the main window and run exec() method from QApplication
*/

#include "Graphic/CustomMainWindow.hpp"

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