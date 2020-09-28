project(Babel)
cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

if (UNIX)
    add_definitions("-fPIC")
endif()
if(WIN32)
    add_compile_options("/std:c++latest")
endif()

include(${PROJECT_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${CMAKE_INCLUDE_PATH})
include_directories(include)
add_executable(babel src/main.cpp include/PortAudio.hpp src/PortAudio.cpp include/IAudio.hpp include/Opus.hpp src/Opus.cpp include/IEncode.hpp include/BabelException.hpp src/QT.cpp include/QT.hpp)
target_link_libraries(babel ${CONAN_LIBS} opus)
target_link_libraries(babel ${CONAN_LIBS} portaudio)
