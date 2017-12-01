cmake_minimum_required(VERSION 2.8)
project(EXPGL)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

get_filename_component(EXP_ROOT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)

list(APPEND CMAKE_MODULE_PATH ${EXP_ROOT_DIR}/EXPUtil)
find_package(EXPUtil REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${EXPUtil_INCLUDE_DIR})

link_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(${EXPUtil_LIBRARY_DIR})

file(GLOB_RECURSE SOURCES "src/EXPGL/*.c" "src/EXPGL/*.cpp" "include/EXPGL/*.hpp" "include/EXPGL/*.h" "include/EXPGL.hpp" "src/glad/glad.c")

add_library(EXPGL STATIC ${SOURCES})

set(EXPGL_LIBRARIES "")

if (APPLE)
	list(APPEND EXPGL_LIBRARIES 
		"-framework OpenGL"
		"-framework CoreVideo" 
		"-framework IOKit" 
		"-framework Cocoa")
endif()

target_link_libraries(EXPGL glfw3 ${EXPGL_LIBRARIES} ${EXPUtil_LIBRARIES})

install(TARGETS EXPGL DESTINATION ${CMAKE_SOURCE_DIR}/lib)