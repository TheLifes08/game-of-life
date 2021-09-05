cmake_minimum_required(VERSION 3.16)
project(game-common)

set(SOURCES Field.cpp)
add_library(game-common SHARED ${SOURCES})
