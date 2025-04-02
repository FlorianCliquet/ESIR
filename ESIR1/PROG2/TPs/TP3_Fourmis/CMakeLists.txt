cmake_minimum_required(VERSION 3.10)
project(Ants)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set Debug as the default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Use pkg-config to find SDL2 and SDL2_gfx
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_gfx REQUIRED SDL2_gfx)

# Define source directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include directories
include_directories(${INCLUDE_DIR} ${SDL2_INCLUDE_DIRS} ${SDL2_gfx_INCLUDE_DIRS})

# Collect all source files
file(GLOB_RECURSE SOURCES
    ${SRC_DIR}/agents-ant/*.cpp
    ${SRC_DIR}/agents-env/*.cpp
    ${SRC_DIR}/renderer/*.cpp
    ${SRC_DIR}/utils/*.cpp
    ${SRC_DIR}/rules/*.cpp
)

# Create executable
add_executable(Ants main.cpp ${SOURCES})

# Link libraries using pkg-config
target_link_libraries(Ants ${SDL2_LIBRARIES} ${SDL2_gfx_LIBRARIES})

# Add compiler flags
target_compile_options(Ants PRIVATE -Wall -Wextra -Wpedantic)

# Enable debug symbols in Debug mode
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Ants PRIVATE
        $<$<CONFIG:Debug>:-g -O0>  # Debug symbols, no optimization
        $<$<CONFIG:Release>:-O3>   # Optimization for Release
    )
endif()
