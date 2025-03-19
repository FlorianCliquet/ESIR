cmake_minimum_required(VERSION 3.16)

# Project name
project(tp2_Liste VERSION 1.0 LANGUAGES CXX)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source files
set(SOURCES src/main.cpp)

# Header files
set(HEADERS src/copier.h src/cyclicNode.h src/liste.hpp)

# Template implementation file (not compiled directly)
set(TEMPLATES src/liste.tpp)

# Add executable
add_executable(ListeTest ${SOURCES} ${HEADERS} ${TEMPLATES})

# Set include directories
target_include_directories(ListeTest PRIVATE src)
