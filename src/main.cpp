#include "game/Engine.h"

int main(int argc, char** argv) {
    Game::Engine engine;
    return engine.execute(argc, argv);
}