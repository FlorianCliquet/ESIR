cmake_minimum_required(VERSION 3.0)
project(vecteur_generique)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER "g++")

if(ENABLE_DEBUG)
    message(STATUS "Compiling in DEBUG mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -DDEBUG")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

file(GLOB SOURCES "src/*.cpp" "src/*.cxx")

add_executable(TP1b ${SOURCES})