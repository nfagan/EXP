cmake_minimum_required(VERSION 2.8)
project(EXPSQL)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

get_filename_component(EXP_ROOT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)

list(APPEND CMAKE_MODULE_PATH ${EXP_ROOT_DIR}/EXPUtil)
find_package(EXPUtil REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${EXPUtil_INCLUDE_DIR})
link_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(${EXPUtil_LIBRARY_DIR})

file(GLOB_RECURSE SOURCES "src/*.c" "src/*.cpp" "include/*.hpp" "include/*.h")

add_library(EXPSQL STATIC ${SOURCES})
target_link_libraries(EXPSQL sqlite3 ${EXPUtil_LIBRARIES})

install(TARGETS EXPSQL DESTINATION ${CMAKE_SOURCE_DIR}/lib)