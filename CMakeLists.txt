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
include_directories(include)
add_executable(babel src/main.cpp include/Audio/PortAudio.hpp src/Audio/PortAudio.cpp include/Audio/IAudio.hpp include/Audio/Opus.hpp src/Audio/Opus.cpp include/Audio/IEncode.hpp src/myUDP.cpp include/BabelException.hpp include/Call.hpp src/Call.cpp include/Network/ClientUDP.hpp include/Network/ServerUDP.hpp src/Network/ClientUDP.cpp src/Network/ServerUDP.cpp include/Network/INetwork.hpp src/Network/NetworkUDP.cpp include/Network/NetworkUDP.hpp)
target_link_libraries(babel ${CONAN_LIBS} Qt5::Widgets)