project(orca)
set(CMAKE_BUILD_TYPE Release)
include_directories(.)
include_directories(cee-utils)
include_directories(common)
file(GLOB SOURCES "*.c")

add_library(orca STATIC ${SOURCES})

target_include_directories(orca PUBLIC .)

install(TARGETS orca DESTINATION /usr/lib)
