cmake_minimum_required(VERSION 3.10)
project(Mixage)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(MIXAGE_SRC_DIR ${CMAKE_SOURCE_DIR}/src/mixage)
set(TEST_SRC_DIR ${CMAKE_SOURCE_DIR}/tests)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE MIXAGE_SRC_FILES ${MIXAGE_SRC_DIR}/*.cpp)
file(GLOB_RECURSE TEST_SRC_FILES ${TEST_SRC_DIR}/*.cpp)

add_executable(Mixage
    main.cpp
    ${MIXAGE_SRC_FILES}
    ${TEST_SRC_FILES}
)

target_include_directories(Mixage PRIVATE ${INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src)

find_library(OUTILS_LIB NAMES outils PATHS ${CMAKE_SOURCE_DIR}/third_party)
if (OUTILS_LIB)
    target_link_libraries(Mixage PRIVATE ${OUTILS_LIB})
else()
    message(FATAL_ERROR "liboutils.a not found!")
endif()
