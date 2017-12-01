cmake_minimum_required(VERSION 2.8)
project(sqlite3)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(include/)

file(GLOB_RECURSE SOURCES "src/*.c" "include/*.hpp" "include/*.h")

add_library(sqlite3 STATIC ${SOURCES})