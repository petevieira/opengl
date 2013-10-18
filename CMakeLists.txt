cmake_minimum_required(VERSION 2.6)
project(opengl)

set(CMAKE_BUILD_TYPE "Release")

# Find GLUT
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found")
endif(NOT GLUT_FOUND)

# Find OPENGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_directories(${OPENGL_LIBRARY_DIRS})
add_definitions(${OPENGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found")
endif(NOT OPENGL_FOUND)

# Set libraries
set(OPENGL_LIBRARIES glut GLU GL)

# Add executables
add_executable(main "src/main.cpp")
target_link_libraries(main ${OPENGL_LIBRARIES})
