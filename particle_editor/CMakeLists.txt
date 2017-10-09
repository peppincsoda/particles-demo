cmake_minimum_required(VERSION 3.9)

file(GLOB SRCS *.cpp)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets)

add_executable(particle_editor WIN32 ${SRCS})

target_include_directories(particle_editor PUBLIC ${MY_ROOT_DIR})

# Use the Widgets module from Qt 5.
target_link_libraries(particle_editor
    particles
    Qt5::Widgets
)

set_target_properties(particle_editor
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
