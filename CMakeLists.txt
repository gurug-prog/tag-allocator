cmake_minimum_required(VERSION 3.21)

project(tag-allocator)

include_directories(include src)

file(GLOB SOURCES "src/*.c")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_definitions(_DEFAULT_SOURCE)
endif()

add_executable(${PROJECT_NAME} ${SOURCES})
