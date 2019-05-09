cmake_minimum_required(VERSION 3.12)
project(fictional_couscous_isn C)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(utils/CompileUtility)
include(utils/InstallUtility)
include(utils/VersionUtility)

set(CMAKE_C_STANDARD 11)

# Options
option(FICTIONAL_COUSCOUS_ISN_INSTALL "Generate installation target" ON)

# Version
set(FICTIONAL_COUSCOUS_ISN_VERSION_MAJOR 1)
set(FICTIONAL_COUSCOUS_ISN_VERSION_MINOR 0)
set(FICTIONAL_COUSCOUS_ISN_VERSION_PATCH 0)
set(FICTIONAL_COUSCOUS_ISN_VERSION_TYPE "indev")

# Generate compile flags.
generate_flags(FICTIONAL_COUSCOUS_ISN_COMPILE_FLAGS "native" 2 true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}${FICTIONAL_COUSCOUS_ISN_COMPILE_FLAGS}")

# Find libraries.
find_package(SDL2 REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_GFX_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} lib)

set(PROJECT_SOURCES src/main.c
    src/game.c
    src/graphics/draw.c
    src/physics/physics.c
    src/ui/ui.c
    src/physics/raytrace.c
    src/maths/vec2d.c
    src/maths/double.c
    src/maths/line.c
    src/graphics/color.c
    src/graphics/texture.c
    src/world/world.c
    lib/easysdl.c
)

set(PROJECT_HEADERS
  src/graphics/draw.h
  src/physics/physics.h
  src/ui/ui.h
  src/game.h
  src/world/world.h
  src/base.h
  src/physics/raytrace.h
  src/maths/vec2d.h
  src/maths/double.h
  src/maths/line.h
  src/graphics/color.h
  src/graphics/texture.h
  src/levels.h
  lib/easysdl.h
)

# Now build the executable.
add_executable(fictional_couscous_isn ${PROJECT_SOURCES} ${PROJECT_HEADERS})
target_link_libraries(fictional_couscous_isn SDL2::SDL2 SDL2::SDL2gfx SDL2::SDL2image SDL2::SDL2mixer SDL2::SDL2ttf)

if(NOT LAMBDA_WINDOWS)
  target_link_libraries(fictional_couscous_isn m)
endif()

# Generate the version header and include it.
generate_version_header("FICTIONAL_COUSCOUS_ISN" "fictional_couscous_isn" ${FICTIONAL_COUSCOUS_ISN_VERSION_MAJOR} ${FICTIONAL_COUSCOUS_ISN_VERSION_MINOR} ${FICTIONAL_COUSCOUS_ISN_VERSION_PATCH} "${FICTIONAL_COUSCOUS_ISN_VERSION_TYPE}")
target_include_directories(fictional_couscous_isn PUBLIC ${CMAKE_BINARY_DIR}/exports)

# Install if the option is on.
if (FICTIONAL_COUSCOUS_ISN_INSTALL)
    install(TARGETS fictional_couscous_isn
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib)

    # Uninstall target.
    setup_uninstall_target()
endif ()
