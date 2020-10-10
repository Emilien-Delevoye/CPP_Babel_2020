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
 * @brief Babel Server initial file
 * @author Paul.S
 * @version 1.0
 * @date 05/10/2020
 *
 * The main file of the Babel server contains the main function.
 * It creates Babel server and start it.
 * This server allows you to choose the port on which to open the server.
*/

#include "Server.hpp"

/*!
 * \brief Help function
 * \param argc (number of arguments)
 *
 * This function will display the usage if number of parameters passed to the program is incorrect
*/

int help(int argc)
{
    if (argc != 2) {
        std::cout << "Usage:" << std::endl;
        std::cout << "./babel_server \033[32mport\033[0m" << std::endl << std::endl;
        std::cout << "Then open your port with :" << std::endl;
        std::cout << "firewall-cmd --zone=public --add-port=\033[32mport\033[0m/tcp" << std::endl;
        return (84);
    }
    return (0);
}

/*!
 * \brief main function
 * \param argc (number of arguments)
 * \param argv (arguments)
 *
 * The main function will start the server with the port passed as parameter and the ip 0.0.0.0
*/

int main(int argc, char **argv)
{
    if (help(argc) == 84)
        return (84);
    Server *server;

    try {
        server = new Server("0.0.0.0", std::atoi(argv[1]));
    } catch (boost::wrapexcept<boost::system::system_error> &e) {
        EP e.what() EL;
        return (84);
    } catch (ServerError &e) {
        EP e.what() EL;
        return (84);
    }
    server->run();
}