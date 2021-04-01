cmake_minimum_required(VERSION 3.6)
project(orca)
## This is for testing only, you won't be able to build all code with this cmake file
## There is no plan to support cmake to build all code.

set(CMAKE_C_STANDARD 99)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_C_FLAGS "-DLIBDISCORD_DEBUG -DBEARSSL -D_XOPEN_SOURCE=700")

set(CMAKE_EXE_LINKER_FLAGS "-static")

file(GLOB CORE_CODE "common/*.h" "common/*.c")
file(GLOB ADAPTER_CODE "*.h" "*.c")
file(GLOB SPECS_CODE "specs-code/*.h" "specs-code/*.c")

file(GLOB MUJS_CODE "mujs/*.h" "mujs/*.c")
file(GLOB SQLITE3_CODE "sqlite3/*.h" "sqlite3/*.c")

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/common)
include_directories(${CMAKE_SOURCE_DIR}/mujs)
include_directories(${CMAKE_SOURCE_DIR}/sqlite3)
include_directories(${CMAKE_SOURCE_DIR}/specs-code)

add_library(discord ${CORE_CODE} ${ADAPTER_CODE} ${SPECS_CODE})

add_library(mujs ${MUJS_CODE})
add_library(sqlite3 ${SQLITE3_CODE})

set(ORCA_INCLUDE_PATH  ${CMAKE_SOURCE_DIR})

add_executable(bot-echo.exe bots/bot-echo.c)
target_link_libraries(bot-echo.exe discord curl bearssl)

add_executable(test-json-scanf.exe test/test-json-scanf.c)
target_link_libraries(test-json-scanf.exe discord)

add_executable(test-json-scanf-array.exe test/test-json-scanf-array.c)
target_link_libraries(test-json-scanf-array.exe discord)

add_executable(test-json-string.exe test/test-json-string.c)
target_link_libraries(test-json-string.exe discord)

add_executable(test-cee.exe test/test-cee.c)
target_link_libraries(test-cee.exe curl bearssl discord)

add_executable(test-json-injector.exe test/test-json-injector.c)

add_executable(test-json-injector-1.exe test/test-json-injector-1.c)

add_executable(test-json-actor.exe test/test-json-actor.c)

add_executable(test-json-extractor.exe test/test-json-extractor.c)
add_executable(test-utf-8.exe test/test-utf8.c)

add_executable(test-json-load.exe common/json-actor.c)

add_executable(test-ntl.exe common/ntl.c common/ntl.h test/test-ntl.c)

add_executable(test-json-struct.exe test/test-json-struct.c)
target_link_libraries(test-json-struct.exe discord m)

add_executable(test-json-struct-gen.exe test/test-json-struct-gen.c)
target_link_libraries(test-json-struct-gen.exe discord m)


add_executable(test-spec.exe test/test-spec.c)
target_link_libraries(test-spec.exe discord m)

file(GLOB B2 "bots-2/*.h" "bots-2/bot-*.c")
add_executable(bot2.exe ${B2})
target_link_libraries(bot2.exe discord mujs sqlite3 curl bearssl)