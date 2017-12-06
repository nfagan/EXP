cmake_minimum_required(VERSION 2.8)
project(ex2)

file(GLOB SOURCES "src/*.cpp" "src/*.hpp")
add_executable(ex2 ${SOURCES})
target_link_libraries(ex2 ${EXP_LIBRARIES})

install(TARGETS ex2 DESTINATION ${EXP_EXAMPLE_BINARY_DIR})