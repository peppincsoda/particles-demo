cmake_minimum_required(VERSION 3.9)

file(GLOB SRCS *.cpp)

add_library(gfx SHARED ${SRCS})

target_include_directories(gfx PUBLIC ${MY_ROOT_DIR})

find_package(Qt5Gui)

target_link_libraries(gfx
    core
    Qt5::Gui
)

set_target_properties(gfx
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
