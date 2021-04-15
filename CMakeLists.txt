cmake_minimum_required (VERSION 3.10.2)

set (CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
project (crisp8-sdl LANGUAGES C)

# Include crisp8 backend
add_subdirectory (external/crisp8)

file (GLOB SOURCES src/*.c src/*.h)

add_executable (crisp8-sdl ${SOURCES})
# Sets the c standard
set_target_properties (crisp8-sdl PROPERTIES C_STANDARD 99)

# Find sdl2
find_package (SDL2 REQUIRED)

if (WIN32)
# This has to come first for some strange reason
    target_link_libraries(crisp8-sdl PRIVATE mingw32)

    # My (working but should not) attempt at including SDL2_Mixer
    # You have to specify SDL2_MIXER_PATH on the command line
    target_include_directories (crisp8-sdl PRIVATE ${SDL2_MIXER_PATH}/include)
    target_link_directories (crisp8-sdl PRIVATE ${SDL2_MIXER_PATH}/lib)

    # Bundle the sdl libraries on windows
    file (GLOB SDL2_MIXER_DEPENDENCIES ${SDL2_MIXER_PATH}/bin/*)
    install (FILES ${SDL2_MIXER_DEPENDENCIES}  DESTINATION bin)
    install (FILES ${SDL2_DIR}/../bin/SDL2.dll DESTINATION bin)

    # WinMain because windows is windows
    target_link_libraries (crisp8-sdl PRIVATE SDL2::SDL2main)
else()
    # See how easy this would be on a sane os
    target_link_libraries (crisp8-sdl PRIVATE SDL2_mixer)
endif ()

target_link_libraries (crisp8-sdl PRIVATE SDL2_mixer SDL2::SDL2 crisp8)

install (TARGETS crisp8-sdl DESTINATION bin)
install (FILES sound/beep.ogg DESTINATION sound)
