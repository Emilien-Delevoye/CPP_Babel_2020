project(Babel)
cmake_minimum_required(VERSION 3.17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

if (UNIX)
    add_definitions("-fPIC")
endif()
if(WIN32)
    add_compile_options("/std:c++latest")
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

QT5_WRAP_CPP(MOC_Files
        client/include/CustomMainWindow.hpp
        client/include/CustomButton.hpp
        client/include/User.hpp
        client/include/UserPage.hpp
        client/include/ConnectionPage.hpp
        client/include/CustomLineEdit.hpp
        client/include/CustomWidget.hpp
        client/include/CustomText.hpp
)

include_directories(
        ${CMAKE_INCLUDE_PATH}

        client/../shared/include
        client/../shared/src
        client/include/NetworkUDP
        client/src/NetworkUDP
        client/include/NetworkTCP
        client/src/NetworkTCP
        client/include/Audio
        client/src/Audio
        client/include
        client/src

        server/include/NetworkTCP/client
        server/include/NetworkTCP/server
        server/include/NetworkTCP
        server/../shared/include
        server/include
        server/src
)

set(CLIENT_SOURCES
        client/src/main.cpp
        client/src/Audio/PortAudio.cpp
        client/src/Audio/Opus.cpp
        client/src/CustomMainWindow.cpp
        client/src/CustomButton.cpp
        client/src/CustomText.cpp
        client/src/CustomLineEdit.cpp
        client/src/ConnectionPage.cpp
        client/src/UserPage.cpp
        client/src/User.cpp
        client/src/CustomWidget.cpp
        client/src/Audio/Audio.cpp
        client/src/NetworkUDP/NetworkUDP.cpp
        client/src/NetworkUDP/ReceiverUDP.cpp
        client/src/NetworkUDP/SenderUDP.cpp
        client/src/Call.cpp
        client/src/NetworkTCP/ClientTcp.cpp
        )

set(CLIENT_INCLUDES
        client/include/Audio/PortAudio.hpp
        client/include/Audio/IAudio.hpp
        client/include/Audio/Opus.hpp
        client/include/Audio/IEncode.hpp
        client/include/CustomMainWindow.hpp
        client/include/CustomButton.hpp
        client/include/enum.hpp
        client/include/CustomText.hpp
        client/include/CustomLineEdit.hpp
        client/include/ConnectionPage.hpp
        client/include/UserPage.hpp
        client/include/User.hpp
        client/include/CustomWidget.hpp
        client/include/Audio/Audio.hpp
        client/include/NetworkUDP/INetworkUDP.hpp
        client/include/NetworkUDP/NetworkUDP.hpp
        client/include/NetworkUDP/ReceiverUDP.hpp
        client/include/NetworkUDP/SenderUDP.hpp
        client/include/Call.hpp
        client/include/NetworkTCP/ClientTcp.hpp
        shared/include/Communication.hpp
        shared/include/BabelException.hpp
)


set(SERVER_SOURCES
        server/src/main.cpp
        server/src/NetworkTCP/InstanceClientTCP.cpp
        server/src/NetworkTCP/ServerTCP.cpp
        server/src/Server.cpp
        shared/src/Users.cpp
)

set(SERVER_INCLUDES
        server/include/NetworkTCP/InstanceClientTCP.hpp
        server/include/NetworkTCP/ServerTCP.hpp
        server/include/Logger.hpp
        server/include/Server.hpp
        shared/include/Communication.hpp
        shared/include/BabelException.hpp
        shared/include/Users.hpp
)

add_executable(babel_client ${MOC_Files} ${CLIENT_SOURCES} ${CLIENT_INCLUDES})

add_executable(babel_server ${SERVER_SOURCES} ${SERVER_INCLUDES})


#target_link_libraries(babel ${CONAN_LIBS} opus)
#target_link_libraries(babel ${CONAN_LIBS} portaudio)
target_link_libraries(babel_server ${CONAN_LIBS})
target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Widgets)
target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Core)

file(GLOB files "*.cpp")
foreach(file ${files})
    get_filename_component(file_basename ${file} NAME_WE)
    add_executable(${file_basename} ${file})
    target_link_libraries(${file_basename} PRIVATE sqlite_orm sqlite3)
endforeach()