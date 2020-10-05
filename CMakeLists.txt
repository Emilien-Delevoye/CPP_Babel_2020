project(Babel)
cmake_minimum_required(VERSION 2.8.12)
if (UNIX)
    add_definitions("-fPIC")
endif()
if(WIN32)
    add_compile_options("/std:c++latest")
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5Widgets CONFIG REQUIRED)

include_directories(${CMAKE_INCLUDE_PATH})
include_directories(
        include
        src/NetworkTCP)
add_executable(babel
        src/main.cpp
        src/Call.cpp

        src/Audio/PortAudio.cpp
        src/Audio/Opus.cpp
        src/Audio/Audio.cpp

        src/NetworkUDP/SenderUDP.cpp
        src/NetworkUDP/ReceiverUDP.cpp
        src/NetworkUDP/NetworkUDP.cpp

        src/NetworkTCP/server/InstanceClientTCP.cpp
        src/NetworkTCP/server/ServerTCP.cpp


        include/Call.hpp
        include/BabelException.hpp

        include/Audio/PortAudio.hpp
        include/Audio/IAudio.hpp
        include/Audio/Opus.hpp
        include/Audio/IEncode.hpp
        include/Audio/Audio.hpp

        include/NetworkUDP/SenderUDP.hpp
        include/NetworkUDP/ReceiverUDP.hpp
        include/NetworkUDP/INetworkUDP.hpp
        include/NetworkUDP/NetworkUDP.hpp

        include/NetworkTCP/server/InstanceClientTCP.hpp
        include/NetworkTCP/server/ServerTCP.hpp
        include/NetworkTCP/Communication.hpp
        include/NetworkTCP/Logger.hpp
        src/NetworkTCP/client/ClientTcp.cpp
        include/NetworkTCP/client/ClientTcp.hpp
        src/Server.cpp
        include/Server.hpp
        include/NetworkTCP/server/CallBacks.hpp
        src/Users.cpp
        include/Users.hpp)

target_link_libraries(babel ${CONAN_LIBS} Qt5::Widgets)

file(GLOB files "*.cpp")
foreach(file ${files})
    get_filename_component(file_basename ${file} NAME_WE)
    add_executable(${file_basename} ${file})
    target_link_libraries(${file_basename} PRIVATE sqlite_orm sqlite3)
endforeach()