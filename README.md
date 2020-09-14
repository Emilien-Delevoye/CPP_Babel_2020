# babel

The project consists in a client/server architecture voice over IP application, similar to Skype or TeamSpeak.

## Build
```
mkdir build && cd build && conan install .. && cmake .. -G "Unix Makefiles" && cmake –build .
```
## OS

The project MUST be OS independent. It has to compile and run in a similar manner on Unix system and Windows systems.
It MUST be built using a CMake and dependencies MUST be handled using conan.
These, and only these, conan repositories may be used:

• conan-center: https://bintray.com/conan/conan-center

• epitech: https://bintray.com/epitech/public-conan

• bincrafters: https://bintray.com/bincrafters/public-conan


## Protocol

The Babel project aims to create an SIP-like Voice Over IP (VOIP) protocol. It MUST be usable over the Internet (no multicast or anything LAN specific).
To test your protocol you MUST write a server and a client implementation.
The protocol MUST be a client/server protocol but voice transport MUST be client to client (the server can have a proxy mode for conference calls or NAT-ed clients).

