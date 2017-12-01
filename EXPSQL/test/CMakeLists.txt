cmake_minimum_required(VERSION 2.8)
project(EXPSQL_test)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)

get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)
get_filename_component(EXP_ROOT_DIR ${PARENT_DIR} DIRECTORY)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

list(APPEND CMAKE_MODULE_PATH "${EXP_ROOT_DIR}/EXPSQL" "${EXP_ROOT_DIR}/EXPUtil")
find_package(EXPSQL REQUIRED)
find_package(EXPUtil REQUIRED)

include_directories(${EXPSQL_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${EXPUtil_INCLUDE_DIR})

link_directories(${EXPSQL_LIBRARY_DIR})
link_directories(${EXPUtil_LIBRARY_DIR})

file(GLOB SOURCES "src/*.cpp" "include/*.hpp")

add_executable(EXPSQL_test ${SOURCES})
target_link_libraries(EXPSQL_test ${EXPSQL_LIBRARIES} ${EXPUtil_LIBRARIES})

install(TARGETS EXPSQL_test DESTINATION ${CMAKE_SOURCE_DIR}/bin)