cmake_minimum_required(VERSION 2.6)
project(FIRSTENGINE)

include_directories(
src
)

add_executable(demo
src/demo/main.cpp
)

target_link)libraries(demo firstengine)

# .h file included to show in VS
add_library(firstengine SHARED
src/firstengine/Core.cpp
src/firstengine/Core.h
)