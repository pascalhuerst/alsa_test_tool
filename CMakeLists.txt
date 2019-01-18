cmake_minimum_required(VERSION 3.2)

project(alsa_test_tool CXX)

file(GLOB_RECURSE SOURCES main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} asound)
