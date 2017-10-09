cmake_minimum_required(VERSION 3.9)

file(GLOB SRCS *.cpp)

add_library(particles SHARED ${SRCS})

target_include_directories(particles PUBLIC ${MY_ROOT_DIR})

target_link_libraries(particles
    mathscript
    gfx
)

set_target_properties(particles
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
