cmake_minimum_required(VERSION 3.24)
project(demo_c__)

set(CMAKE_CXX_STANDARD 17)
set(SFML_ROOT "C:/dependencies/SFML-2.5.1")
set(DEMO_SOURCE source/main.cpp)

find_package(SFML 2.5 REQUIRED COMPONENTS system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

add_executable(demo_c__ ${DEMO_SOURCE})
if(SFML_FOUND)
    target_link_libraries(demo_c__ PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
endif()