cmake_minimum_required (VERSION 3.10.2)

set (CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project (crisp8-sdl LANGUAGES C)

# Include crisp8 backend
add_subdirectory (external/crisp8)

# Find sdl2
find_package (SDL2 REQUIRED)

file (GLOB SOURCES src/*.c src/*.h)

add_executable (crisp8-sdl ${SOURCES})

# Sets the c standard
set_target_properties (crisp8-sdl PROPERTIES C_STANDARD 99)

target_link_libraries (crisp8-sdl PRIVATE SDL2::SDL2 SDL2_mixer crisp8)

if (WIN32)
    target_link_libraries (crisp8-sdl PRIVATE SDL2::SDL2main)
endif ()

# Defines which part of the library are needed by the user
install (TARGETS crisp8-sdl DESTINATION bin)
