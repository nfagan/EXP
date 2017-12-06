cmake_minimum_required(VERSION 2.8)
project(EXP_examples)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/../cmake)

find_package(EXP REQUIRED)

include_directories(${EXP_INCLUDE_DIRS})
link_directories(${EXP_LIBRARY_DIRS})

add_subdirectory(ex1)
add_subdirectory(ex2)