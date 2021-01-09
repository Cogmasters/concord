cmake_minimum_required(VERSION 3.8)
project(orca)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_C_FLAGS "-DJSMN_PARENT_LINKS -DJSMN_STRICT -fPIC -DLIBDISCORD_DEBUG -D_XOPEN_SOURCE=700 --include=stdint.h --include=stdbool.h")
set(CMAKE_CXX_FLAGS "-DJSMN_PARENT_LINKS -DJSMN_STRICT -fPIC -D_XOPEN_SOURCE=700")
#set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -fpermissive")

set(CMAKE_EXE_LINKER_FLAGS "")

set(JSON_SCANF
        debug.h
        jscon-common.c
        jscon-common.h
        jsmn.h
        json-scanf.c
        json-scanf.h)

set(SOURCE_FILES
        curl-websocket-utils.c
        curl-websocket.c
        curl-websocket.h
        discord-api.c
        discord-common.h
        discord-public-guild.c
        discord-public-user.c
        discord-public.c
        discord-tool-debug.h
        discord-websockets.c
        libdiscord.h
        settings.c
        settings.h
        ${JSON_SCANF})



set(ORCA_INCLUDE_PATH  ${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR})


add_executable(test-api.exe ${SOURCE_FILES} test-api.c)
target_link_libraries(test-api.exe curl ssl crypto)

add_executable(test-ws.exe ${SOURCE_FILES} test-ws.c)
add_executable(test-json-scanf.exe ${JSON_SCANF} test-json-scanf.c)