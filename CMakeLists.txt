cmake_minimum_required(VERSION 3.27.1)

project(elangine)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Initialize the SRCFILES variable
# Add the source directory to the include path for the target 'src'
add_executable(${PROJECT_NAME} src/main.c)
add_subdirectory(src)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw m)


# Set the source directory for shader files
set(ASSETS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/assets)
set(ASSETS_DEST_DIR ${CMAKE_BINARY_DIR})
# Copy asset files during the build process
file(COPY ${ASSETS_SOURCE_DIR} DESTINATION ${ASSETS_DEST_DIR})

# Link the libraries listed in SRCFILES
