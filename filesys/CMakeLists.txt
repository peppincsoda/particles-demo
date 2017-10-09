cmake_minimum_required(VERSION 3.9)

file(GLOB SRCS *.cpp)

add_library(filesys SHARED ${SRCS})

set_target_properties(filesys
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
