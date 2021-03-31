cmake_minimum_required(VERSION 3.6)
project(orca)
## This is for testing only, you won't be able to build all code with this cmake file
## There is no plan to support cmake to build all code.

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_COMPILER stensal-c)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_C_FLAGS "-DLIBDISCORD_DEBUG -DBEARSSL -D_XOPEN_SOURCE=700")

set(CMAKE_EXE_LINKER_FLAGS "-static")

set(COMMON
        common/curl-websocket.h
        common/json-actor-boxed.h
        common/json-scanf.h
        common/orka-config.h
        common/orka-utils.h
        common/specs.h
        common/utf8.h
        common/jsmn.h
        common/json-actor.h
        common/ntl.h
        common/orka-debug.h
        common/scheduler.h
        common/user-agent.h
        common/websockets.h
        common/curl-websocket.c
        common/json-actor-boxed.c
        common/json-printf.c
        common/json-string.c
        common/ntl.c
        common/orka-config.c
        common/scheduler.c
        common/websockets.c
        common/curl-websocket-utils.c
        common/json-actor.c
        common/json-scanf.c
        common/json-struct.c
        common/orka-utils.c
        common/user-agent.c
        discord-adapter.c
        discord-client.c
        discord-gateway.c
        discord-misc.c
        discord-user.c
        github-v3-git-op.c
        slack-client.c
        discord-channel.c
        discord-emoji.c
        discord-guild.c
        discord-ratelimit.c
        github-v3-adapter.c
        slack-adapter.c
        slack-socketmode.c
        discord-common.h
        github-v3-adapter.h
        github-v3.h
        libdiscord.h
        slack-common.h
        slack.h)

file(GLOB SPECS_CODE
        "specs-code/*.h" "specs-code/*.c")


include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/common)
include_directories(${CMAKE_SOURCE_DIR}/mujs)
include_directories(${CMAKE_SOURCE_DIR}/sqlite3)
include_directories(${CMAKE_SOURCE_DIR}/specs-code)

add_library(discord ${COMMON} ${SPECS_CODE})


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
        common/json-actor.c)

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