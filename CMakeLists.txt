cmake_minimum_required(VERSION 3.16)
project(game-of-life)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_subdirectory(src/game)

add_executable(game-of-life src/main.cpp)
target_link_libraries(game-of-life engine sfml-graphics sfml-audio)