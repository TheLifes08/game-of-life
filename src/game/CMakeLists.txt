cmake_minimum_required(VERSION 3.16)
project(engine)

add_subdirectory(common)
add_subdirectory(gui)

set(SOURCES Engine.cpp)
add_library(engine SHARED ${SOURCES})
target_link_libraries(engine game-gui game-common)
