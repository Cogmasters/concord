cmake_minimum_required(VERSION 3.8)
project(libdiscord)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES cee.cpp cee.hpp jsmn.h)

add_executable(test_jsmn.exe ${SOURCE_FILES} test_jsmn.cpp)
add_executable(simple.exe ${SOURCE_FILES} simple.c)