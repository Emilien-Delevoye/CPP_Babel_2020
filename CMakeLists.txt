project(Babel)
cmake_minimum_required(VERSION 2.8.12)
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
        include/CustomMainWindow.hpp
        include/CustomButton.hpp
        include/User.hpp
        include/UserPage.hpp
        include/ConnectionPage.hpp
        include/CustomLineEdit.hpp
        include/CustomWidget.hpp
        include/CustomText.hpp
        )

include_directories(${CMAKE_INCLUDE_PATH})
include_directories(include)
add_executable(babel ${MOC_Files}
        src/main.cpp
        include/Audio/PortAudio.hpp
        src/Audio/PortAudio.cpp
        include/Audio/IAudio.hpp
        include/Audio/Opus.hpp
        src/Audio/Opus.cpp
        include/Audio/IEncode.hpp
        include/BabelException.hpp
        src/CustomMainWindow.cpp
        include/CustomMainWindow.hpp
        src/CustomButton.cpp
        include/CustomButton.hpp
        include/enum.hpp
        src/CustomText.cpp
        include/CustomText.hpp
        src/CustomLineEdit.cpp
        include/CustomLineEdit.hpp
        src/ConnectionPage.cpp
        include/ConnectionPage.hpp
        src/UserPage.cpp
        include/UserPage.hpp
        src/User.cpp
        include/User.hpp
        src/CustomWidget.cpp
        include/CustomWidget.hpp
        src/Audio/Audio.cpp
        include/Audio/Audio.hpp
        include/Network/INetwork.hpp
        include/Network/NetworkUDP.hpp
        include/Network/ReceiverUDP.hpp
        include/Network/SenderUDP.hpp
        src/NetworkUDP/NetworkUDP.cpp
        src/NetworkUDP/ReceiverUDP.cpp
        src/NetworkUDP/SenderUDP.cpp
        src/Call.cpp
        include/Call.hpp)
#target_link_libraries(babel ${CONAN_LIBS} opus)
#target_link_libraries(babel ${CONAN_LIBS} portaudio)
target_link_libraries(babel ${CONAN_LIBS} Qt5::Widgets)
target_link_libraries(babel ${CONAN_LIBS} Qt5::Core)