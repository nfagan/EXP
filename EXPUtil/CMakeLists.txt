cmake_minimum_required(VERSION 2.8)
project(EXPUtil)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(
	include/
	include/EXPUtil/assert 
	include/EXPUtil/data 
	include/EXPUtil/thread
)

file(GLOB_RECURSE SOURCES "src/*.cpp" "include/*.hpp" "include/*.h")

add_library(EXPUtil STATIC ${SOURCES})

install(TARGETS EXPUtil DESTINATION ${CMAKE_SOURCE_DIR}/lib)



