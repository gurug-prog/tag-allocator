cmake_minimum_required(VERSION 3.21)

project(tag-allocator)

include_directories(include src)

file(GLOB SOURCES "src/*")

add_executable(${PROJECT_NAME} ${SOURCES})
