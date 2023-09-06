cmake_minimum_required(VERSION 3.26.1)

project(elangine)

include_directories(src)

find_package(glfw3)
find_package(cglm)

add_executable(${PROJECT_NAME} src/main.c)

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} glfw m)
add_compile_options(-Wall -Werror -Wno-error=maybe-uninitialized)
add_compile_definitions(CGLM_FORCE_LEFT_HANDED)

set(ASSETS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/assets)
set(ASSETS_DEST_DIR ${CMAKE_BINARY_DIR})
file(COPY ${ASSETS_SOURCE_DIR} DESTINATION ${ASSETS_DEST_DIR})

configure_file(${CMAKE_SOURCE_DIR}/dll/glfw3.dll ${CMAKE_BINARY_DIR} COPYONLY)