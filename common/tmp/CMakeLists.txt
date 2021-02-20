cmake_minimum_required(VERSION 3.8)
project(libdiscord)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_C_FLAGS "-DJSMN_PARENT_LINKS -DJSMN_STRICT")
set(CMAKE_CXX_FLAGS "-DJSMN_PARENT_LINKS -DJSMN_STRICT")
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(SOURCE_FILES cee.cpp cee.hpp jsmn.h)

add_executable(test_jsmn.exe ${SOURCE_FILES} test_jsmn.cpp)
add_executable(simple.exe ${SOURCE_FILES} simple.c)