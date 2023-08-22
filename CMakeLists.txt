cmake_minimum_required(VERSION 3.27.1)

project(elangine)

# test comment
include_directories(src)

find_package(glfw3)

add_executable(${PROJECT_NAME} src/main.c)

add_subdirectory(src)

set(ASSETS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/assets)
set(ASSETS_DEST_DIR ${CMAKE_BINARY_DIR})
file(COPY ${ASSETS_SOURCE_DIR} DESTINATION ${ASSETS_DEST_DIR})