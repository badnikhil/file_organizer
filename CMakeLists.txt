cmake_minimum_required(VERSION 3.10)

project(file_organizer C)
set(CMAKE_C_STANDARD 99)

include_directories(.)
file(GLOB SOURCES "*.c")
file(GLOB HEADERS "*.h")


set(COMMON_COMPILE_OPTIONS -O2 -DNDEBUG -s -flto -Wall -Wextra -std=c99 -fno-strict-aliasing)


add_executable(file_organizer ${SOURCES} ${HEADERS})

target_compile_options(file_organizer PRIVATE ${COMMON_COMPILE_OPTIONS})


