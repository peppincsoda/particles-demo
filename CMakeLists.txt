cmake_minimum_required(VERSION 3.9)

project(particle_editor)

enable_testing()

set(MY_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

add_subdirectory(mathscript)
add_subdirectory(filesys)
add_subdirectory(gfx)
add_subdirectory(particles)
add_subdirectory(particle_editor)
add_subdirectory(test)
