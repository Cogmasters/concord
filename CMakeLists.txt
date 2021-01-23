cmake_minimum_required(VERSION 3.8)
project(orca)
## This is for testing only, you won't be able to build all code with this cmake file
## There is no plan to support cmake to build all code.



set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_C_FLAGS "-DLIBDISCORD_DEBUG -D_XOPEN_SOURCE=700 --include=stdint.h --include=stdbool.h")
set(CMAKE_CXX_FLAGS "-DLIBDISCORD_DEBUG -D_XOPEN_SOURCE=700 -DJSON_SCANF_DEBUG")

set(CMAKE_EXE_LINKER_FLAGS "")

set(JSON_SCANF
        json-common.h
        jsmn.h
        json-scanf.c
        json-printf.c
        json-scanf.h)

set(SOURCE_FILES
        curl-websocket-utils.c
        curl-websocket.c
        curl-websocket.h
        discord-api.c
        discord-common.h
        discord-public.c
        discord-public-guild.c
        discord-public-user.c
        discord-tool-debug.h
        discord-utils.c
        discord-websockets.c
        libdiscord.h
        settings.c
        settings.h
        discord-api.cpp
        ${JSON_SCANF})

set(GITHUB_FILES
        http-common.h
        github-v3.h
        github-v3-ua.cpp
        github-v3-git-database.cpp
        github-v3-repositories.cpp
        settings.h
        settings.c
        ${JSON_SCANF})

set(CEE_FILES
        http-common.h
        tester.h
        tester-ua.cpp
        settings.h
        settings.c
        ${JSON_SCANF})


set(ORCA_INCLUDE_PATH  ${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR})


add_executable(test-api.exe ${SOURCE_FILES} test-api.c)
target_link_libraries(test-api.exe curl ssl crypto)

add_executable(test-ws.exe ${SOURCE_FILES} test-ws.c)
add_executable(test-json-scanf.exe ${JSON_SCANF} test-json-scanf.c)

add_executable(test-json-scanf-array.exe ${JSON_SCANF} test-json-scanf-array.c)

add_executable(test-git.exe ${GITHUB_FILES}  test-git.cpp)
target_link_libraries(test-git.exe curl ssl crypto)

add_executable(test-cee.exe ${CEE_FILES}  test-cee.cpp)
target_link_libraries(test-cee.exe curl ssl crypto)