cmake_minimum_required(VERSION 2.8)
project(EXP_ex1)

file(GLOB SOURCES "src/*.cpp" "src/*.hpp")
add_executable(EXP_ex1 ${SOURCES})
target_link_libraries(EXP_ex1 ${EXP_LIBRARIES})

install(TARGETS EXP_ex1 DESTINATION ${EXP_EXAMPLE_BINARY_DIR})