cmake_minimum_required(VERSION 3.16)
project(game-gui)

set(SOURCES Scene.cpp WindowManager.cpp GameScene.cpp)
add_library(game-gui SHARED ${SOURCES})
