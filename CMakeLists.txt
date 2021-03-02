cmake_minimum_required(VERSION 3.8)
project(orca)
## This is for testing only, you won't be able to build all code with this cmake file
## There is no plan to support cmake to build all code.



set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_C_FLAGS "-DLIBDISCORD_DEBUG -DJSON_SCANF_DEBUG -D_XOPEN_SOURCE=700")
set(CMAKE_CXX_FLAGS "-DLIBDISCORD_DEBUG -D_XOPEN_SOURCE=700 -Wno-write-strings -Wno-c++11-compat-deprecated-writable-strings")

set(CMAKE_EXE_LINKER_FLAGS "")

set(JSON_SCANF
        common/jsmn.h
        common/ntl.c
        common/ntl.h
        common/json-scanf.c
        common/json-printf.c
        common/json-string.c
        common/json-scanf.h)

set(SOURCE_FILES
        common/curl-websocket-utils.c
        common/curl-websocket.c
        common/curl-websocket.h
        discord-common.h
        discord-public.cpp
        discord-public-guild.cpp
        discord-public-user.cpp
        discord-websockets.cpp
        libdiscord.h
        ${JSON_SCANF})

set(ORKA_FILES
        common/orka-utils.c
        common/orka-utils.h)

set(GITHUB_FILES
        common/http-common.h
        common/http-common.c
        github-v3.hpp
        github-v3-user-agent.cpp
        github-v3-git-op.cpp
        ${JSON_SCANF}
        ${ORKA_FILES})

set(CEE_FILES
        common/http-common.h
        common/http-common.c
        orka-user-agent.hpp
        orka-user-agent.cpp
        ${JSON_SCANF})


set(ORCA_INCLUDE_PATH  ${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/common)


add_executable(test-api.exe ${SOURCE_FILES} test/test-api.cpp)
target_link_libraries(test-api.exe curl ssl crypto)

add_executable(test-ws.exe ${SOURCE_FILES} test/test-ws.cpp)
add_executable(test-json-scanf.exe ${JSON_SCANF} test/test-json-scanf.c)

add_executable(test-json-scanf-array.exe ${JSON_SCANF} ${ORKA_FILES}
        common/json-actor.c
        test/test-json-scanf-array.c)
target_link_libraries(test-json-scanf-array.exe m)

add_executable(test-json-string.exe ${JSON_SCANF} ${ORKA_FILES}
        test/test-json-string.c)
target_link_libraries(test-json-string.exe m)

add_executable(test-git.exe ${GITHUB_FILES}  test/test-git.cpp)
target_link_libraries(test-git.exe curl ssl crypto)

add_executable(test-git2.exe
        ${JSON_SCANF}
        common/json-actor.c
        ${GITHUB_FILES} ${ORKA_FILES}
        test/test-git2.cpp)

target_link_libraries(test-git2.exe curl ssl crypto)

add_executable(test-cee.exe ${CEE_FILES} ${ORKA_FILES} test/test-cee.cpp)
target_link_libraries(test-cee.exe curl ssl crypto)

add_executable(test-json-injector.exe
        common/ntl.c
        common/json-string.c
        common/json-actor.c
        test/test-json-injector.c)

add_executable(test-json-injector-1.exe
        common/ntl.c
        common/json-string.c
        common/json-actor.c
        test/test-json-injector-1.c)

add_executable(test-json-actor.exe
        common/ntl.c
        common/json-string.c
        test/test-json-actor.c)

add_executable(test-json-extractor.exe
        common/ntl.c
        common/json-string.c
        test/test-json-extractor.c)


add_executable(test-utf-8.exe
        test/test-utf8.c)


add_executable(test-json-load.exe
        common/json-string.c
        common/json-scanf.c
        common/orka-utils.c
        common/ntl.c
        common/json-actor.c
        test/test-json-load.cpp)

add_executable(test-ntl.exe
        common/ntl.c
        common/ntl.h
        test/test-ntl.c)


add_executable(test-json-struct.exe
        common/orka-utils.c
        common/json-actor.c
        common/ntl.c
        common/json-string.c
        common/json-scanf.c
        common/json-printf.c
        test/test-json-struct.c)
target_link_libraries(test-json-struct.exe m)

add_executable(test-json-struct-gen.exe
        common/orka-utils.c
        common/json-actor.c
        common/ntl.c
        common/json-string.c
        common/json-scanf.c
        common/json-printf.c
        test/test-json-struct-gen.c)
target_link_libraries(test-json-struct-gen.exe m)


add_executable(test-spec.exe
        common/orka-utils.c
        common/json-actor.c
        common/ntl.c
        common/json-string.c
        common/json-scanf.c
        common/json-printf.c
        test/test-spec.c)
target_link_libraries(test-spec.exe m)