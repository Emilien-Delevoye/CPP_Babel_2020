project(Babel)
cmake_minimum_required(VERSION 3.17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

if (UNIX)
    add_definitions("-fPIC")
endif()
if(WIN32)
    add_compile_options("/std:c++latest")
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEF:my_defs.def /NODEFAULTLIB")
    add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

QT5_WRAP_CPP(MOC_Files
        client/include/Graphic/CustomMainWindow.hpp
        client/include/Graphic/CustomButton.hpp
        client/include/Graphic/User.hpp
        client/include/Graphic/AUser.hpp
        client/include/Graphic/UserPage.hpp
        client/include/Graphic/ConnectionPage.hpp
        client/include/Graphic/CustomLineEdit.hpp
        client/include/Graphic/CustomWidget.hpp
        client/include/Graphic/CustomText.hpp
)

include_directories(
        ${CMAKE_INCLUDE_PATH}

        client/include/NetworkUDP
        client/src/NetworkUDP
        client/include/NetworkTCP
        client/src/NetworkTCP
        client/include/Audio
        client/src/Audio
        client/include
        client/src

        server/include/NetworkTCP
        server/src/NetworkTCP
        server/include
        server/src

        shared/include
        shared/src
)

set(CLIENT_SOURCES
        client/src/main.cpp
        client/src/Audio/AudioIO.cpp
        client/src/Audio/Encode.cpp
        client/src/Graphic/CustomMainWindow.cpp
        client/src/Graphic/CustomButton.cpp
        client/src/Graphic/CustomText.cpp
        client/src/Graphic/CustomLineEdit.cpp
        client/src/Graphic/ConnectionPage.cpp
        client/src/Graphic/UserPage.cpp
        client/src/Graphic/User.cpp
        client/src/Graphic/CustomWidget.cpp
        client/src/Audio/Audio.cpp
        client/src/NetworkUDP/NetworkUDP.cpp
        client/src/NetworkUDP/ReceiverUDP.cpp
        client/src/NetworkUDP/SenderUDP.cpp
        client/src/Audio/Call.cpp
        client/src/NetworkTCP/ClientTcp.cpp
)

set(CLIENT_INCLUDES
        client/include/Audio/AudioIO.hpp
        client/include/Audio/IAudio.hpp
        client/include/Audio/Encode.hpp
        client/include/Audio/IEncode.hpp
        client/include/Graphic/CustomMainWindow.hpp
        client/include/Graphic/CustomButton.hpp
        client/include/Graphic/enum.hpp
        client/include/Graphic/CustomText.hpp
        client/include/Graphic/CustomLineEdit.hpp
        client/include/Graphic/ConnectionPage.hpp
        client/include/Graphic/UserPage.hpp
        client/include/Graphic/User.hpp
        client/include/Graphic/CustomWidget.hpp
        client/include/Audio/Audio.hpp
        client/include/NetworkUDP/INetworkUDP.hpp
        client/include/NetworkUDP/NetworkUDP.hpp
        client/include/NetworkUDP/ReceiverUDP.hpp
        client/include/NetworkUDP/SenderUDP.hpp
        client/include/Audio/Call.hpp
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
        client/include/Graphic/AUser.hpp)

set(SERVER_INCLUDES
        server/include/NetworkTCP/InstanceClientTCP.hpp
        server/include/NetworkTCP/ServerTCP.hpp
        server/include/Logger.hpp
        server/include/Server.hpp
        shared/include/Communication.hpp
        shared/include/BabelException.hpp
        shared/include/Users.hpp
        server/include/NetworkTCP/IServerTcp.hpp)

add_executable(babel_client ${MOC_Files} ${CLIENT_SOURCES} ${CLIENT_INCLUDES})

add_executable(babel_server ${SERVER_SOURCES} ${SERVER_INCLUDES})

## NOT USED ##
#target_link_libraries(babel ${CONAN_LIBS} opus)
#target_link_libraries(babel ${CONAN_LIBS} portaudio)

## TMP CHANGEMENT ##
target_link_libraries(babel_server ${CONAN_LIBS})
target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Widgets)
target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Core)

file(GLOB files "*.cpp")
foreach(file ${files})
    get_filename_component(file_basename ${file} NAME_WE)
    add_executable(${file_basename} ${file})
    target_link_libraries(${file_basename} PRIVATE sqlite_orm sqlite3)
endforeach()

if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "/DWIN32 /D_WINDOWS /EHsc /WX /wd4355 /wd4251 /wd4250 /wd4996" CACHE STRING "Debug compiler flags" FORCE)
    set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
    set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
    set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
    set(Boost_USE_MULTITHREADED      ON)
    set(Boost_USE_STATIC_RUNTIME     OFF)
    find_package(Boost 1.71.0 COMPONENTS serialization)
    if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        target_link_libraries(babel_client ${Boost_LIBRARIES})
        target_link_libraries(babel_server ${Boost_LIBRARIES})
    endif()
endif()
