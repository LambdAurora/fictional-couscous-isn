cmake_minimum_required(VERSION 3.13)
project(fictional_couscous_isn C)

set(CMAKE_C_STANDARD 11)

set(PROJECT_SOURCES src/main.c
  src/graphics/raytracing.c
  src/physics/physics.c
  src/ui/ui.c
)
set(PROJECT_HEADERS
  src/graphics/raytracing.h
  src/physics/physics.h
  src/ui/ui.h
)

add_executable(fictional_couscous_isn ${PROJECT_SOURCES} ${PROJECT_HEADERS})
