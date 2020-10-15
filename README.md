# Babel

The project consists in a client/server architecture voice over IP application, similar to Skype or TeamSpeak.

## Build
- Linux
```
mkdir build && cd build && conan install .. && cmake .. -G "Unix Makefiles" && cmake –build . && make
```
- Windows (powershell)
```
mkdir build ; cd build ; conan install .. ; cmake .. ; cmake –build .
```

## Required

**Windows**
- conan=1.29.0
- cmake=3.17
- Visual studio

**Linux**
- conan=1.29.0
- cmake=3.17
- make=4.2.1

Add needed remotes <br>
conan remote add conan https://api.bintray.com/conan/conan/conan-center <br>
conan remote add epitech https://api.bintray.com/conan/epitech/public-conan <br>
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan <br>


## Use the server

To allow other computers connecting to the server you have to open your ports.
- Linux :

          firewall-cmd --zone=public --add-port=port/tcp.
    - The port is the *port* number passed as parameter to the server.
- Windows : When needed, you'll get a popup that allow you to easily open your ports.

## Use the clients

To use the client you have to open your udp ports. Used port are 4241 and 4242.
- Linux :

          firewall-cmd --zone=public --add-port=4242/tcp
          firewall-cmd --zone=public --add-port=4241/tcp
- Windows : When needed, you'll get a popup that allow you to easily open your ports.
   
Please do not run the program in an application integrated terminal. Audio devices are not always available from there.

**Warning** : if use the client on the same pc as the server, you should use the real pc ip instead of '127.0.0.1'
              otherwise you'll get issue with your sound transmission. 
              
## Execution
Go to the build/bin directory and execute the wanted binary.

## Custom the graphic

Our graphic UI work with QSS, the a CSS solution to design QT windows. <br>
You can edit the styles/styles.qss to customise the UI. (color, width, height ...)


## OS

The project MUST be OS independent. It has to compile and run in a similar manner on Unix system and Windows systems.
It MUST be built using a CMake and dependencies MUST be handled using conan.
These, and only these, conan repositories may be used:

- conan-center: https://bintray.com/conan/conan-center
- epitech: https://bintray.com/epitech/public-conan
- bincrafters: https://bintray.com/bincrafters/public-conan


## Protocol

The Babel project aims to create an SIP-like Voice Over IP (VOIP) protocol. It MUST be usable over the Internet (no multicast or anything LAN specific).
To test your protocol you MUST write a server and a client implementation.
The protocol MUST be a client/server protocol but voice transport MUST be client to client (the server can have a proxy mode for conference calls or NAT-ed clients).

## Documentation

This project is documented with doxygen
to get the documentation use the command :<br>
```doxygen doc/Doxyfile && your-browser doc/html/index.html``` <br>
at the root of the project. Change "you-browser" with you browser binary.