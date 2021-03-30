cmake_minimum_required(VERSION 3.6)
project(orca)
## This is for testing only, you won't be able to build all code with this cmake file
## There is no plan to support cmake to build all code.

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER stensal-c)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_C_FLAGS "-DLIBDISCORD_DEBUG -DJSON_SCANF_DEBUG -D_XOPEN_SOURCE=700")
set(CMAKE_CXX_FLAGS "-DLIBDISCORD_DEBUG -D_XOPEN_SOURCE=700 -Wno-write-strings -Wno-c++11-compat-deprecated-writable-strings")

set(CMAKE_EXE_LINKER_FLAGS "-static")

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
        discord-channel.c
        discord-guild.c
        discord-user.c
        discord-gateway.c
        libdiscord.h
        ${JSON_SCANF})

set(ORKA_FILES
        common/orka-utils.c
        common/orka-utils.h)

set(GITHUB_FILES
        github-v3.h
        github-v3-user-agent.c
        github-v3-git-op.c
        ${JSON_SCANF}
        ${ORKA_FILES})

set(CEE_FILES ${JSON_SCANF})

set(MUJS_FILES
        mujs/one.c
        mujs/mujs.h
        )


set(ORCA_INCLUDE_PATH  ${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/common)
include_directories(${CMAKE_SOURCE_DIR}/mujs)
include_directories(${CMAKE_SOURCE_DIR}/sqlite3)



add_executable(test-json-scanf.exe ${JSON_SCANF} test/test-json-scanf.c)

add_executable(test-json-scanf-array.exe ${JSON_SCANF} ${ORKA_FILES}
        common/json-actor.c
        test/test-json-scanf-array.c)
target_link_libraries(test-json-scanf-array.exe m)

add_executable(test-json-string.exe ${JSON_SCANF} ${ORKA_FILES}
        test/test-json-string.c)
target_link_libraries(test-json-string.exe m)

#add_executable(test-git2.exe
#        ${JSON_SCANF}
#        common/json-actor.c
#        ${GITHUB_FILES} ${ORKA_FILES}
#        test/test-git2.c)

#target_link_libraries(test-git2.exe curl ssl crypto)

add_executable(test-cee.exe ${CEE_FILES} test/test-cee.c)
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