cmake_minimum_required(VERSION 3.0)
project(vecteur)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER "g++")

option(USE_DEBUG "Enable debug mode with extra logging" OFF)
option(USE_AVX "Enable AVX optimizations" OFF)

if(ENABLE_DEBUG)
    message(STATUS "Compiling in DEBUG mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -DDEBUG")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

if(ENABLE_AVX)
    message(STATUS "Compiling with AVX optimizations")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx -mfma -D__AVX__ -O3")
endif()

file(GLOB SOURCES "src/*.cpp" "src/*.cxx")

add_executable(TP1 ${SOURCES})
