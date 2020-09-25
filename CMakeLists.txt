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
add_executable(babel src/main.cpp include/PortAudio.hpp src/PortAudio.cpp include/IAudio.hpp include/Opus.hpp src/Opus.cpp include/IEncode.hpp)
target_link_libraries(babel ${CONAN_LIBS} Qt5::Widgets)
