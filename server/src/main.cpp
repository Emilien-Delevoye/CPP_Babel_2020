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
 * Before doing anything please install the following dependencies :
 * - [...]
 * - [...]
 * \subsection d Compile the Babel !
 * Once the dependencies are installed, you have to use the "make" command to compile the Babel.
 * <br>
 * Our project works with a CMakeLists.txt (do not remove it or you won't be able to compile anymore).
 * <br>
 * If you make any changes to our code, you may want to use "make re" to recompile all project's files.
 *
 * \subsection e How to launch Babel
 * Now that you have compiled all the files needed to run the Babel, you should find the "babel" binary by going in the "build" directory and then in the "bin" directory.
 * <br>
 * Once found, you can do "./babel", and the magic will come.
 * <br>
 * \warning Be sure that all the dependencies are correctly installed before compiling our project.
 * If it's not case you will have some error during the compilation.
 *
 *
 * \authors Cyprien Ricques <br> Emilien Delevoye <br> Paul Surrans
*/

/*!
 * @file main.cpp
 * @brief Babel initial file
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 *
 * The main file of the Babel contain the main function.
 * It creates Babel application and set the relation with the styles.qss file to customise our application.
 * Moreover, it creates the main window and run exec() method from QApplication
*/

#include "Server.hpp"

int main(int argc, char **argv)
{
    if (argc != 3) {
        std::cout << "Usage:" << std::endl;
        std::cout << "./babel_server ip port" << std::endl << std::endl;
        std::cout << "Then open your port with :" << std::endl;
        std::cout << "firewall-cmd --zone=public --add-port=server_port/tcp" << std::endl;
        return (84);
    }
    std::string ip(argv[1]);
    Server server(ip, std::atoi(argv[2]));
    server.run();
}