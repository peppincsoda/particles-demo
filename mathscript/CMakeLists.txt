cmake_minimum_required(VERSION 2.8)

file(GLOB SRCS *.cpp)

add_library(mathscript SHARED ${SRCS})

set_target_properties(mathscript
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
