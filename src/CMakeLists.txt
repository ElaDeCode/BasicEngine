target_sources(${PROJECT_NAME} PRIVATE gl.c)

add_subdirectory(modules)
add_subdirectory(objects)
add_subdirectory(math)

target_link_libraries(${PROJECT_NAME} glfw m)