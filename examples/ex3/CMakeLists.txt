cmake_minimum_required(VERSION 2.8)
project(ex3)

file(GLOB SOURCES "src/*.cpp" "src/*.hpp")
add_executable(ex3 ${SOURCES})
target_link_libraries(ex3 ${EXP_LIBRARIES})

install(TARGETS ex3 DESTINATION ${EXP_EXAMPLE_BINARY_DIR})