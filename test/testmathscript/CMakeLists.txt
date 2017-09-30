cmake_minimum_required(VERSION 2.8)

file(GLOB SRCS *.cpp)

add_executable(testmathscript ${SRCS})

target_include_directories(testmathscript PUBLIC ${MY_ROOT_DIR})

target_link_libraries(testmathscript
    mathscript
    libgtest
    libgmock
)

set_target_properties(testmathscript
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_test(NAME testmathscript COMMAND testmathscript)
