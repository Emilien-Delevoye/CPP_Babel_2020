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
add_executable(babel src/main.cpp include/Audio/PortAudio.hpp src/Audio/PortAudio.cpp include/Audio/IAudio.hpp include/Audio/Opus.hpp src/Audio/Opus.cpp include/Audio/IEncode.hpp include/BabelException.hpp include/Call.hpp src/Call.cpp include/Network/SenderUDP.hpp include/Network/ReceiverUDP.hpp src/NetworkUDP/SenderUDP.cpp src/NetworkUDP/ReceiverUDP.cpp include/Network/INetwork.hpp src/NetworkUDP/NetworkUDP.cpp include/Network/NetworkUDP.hpp include/Audio/Audio.hpp src/Audio/Audio.cpp)
target_link_libraries(babel ${CONAN_LIBS} Qt5::Widgets)