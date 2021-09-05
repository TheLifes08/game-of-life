#include "Engine.h"
#include "gui/GameScene.h"

int Game::Engine::execute() {
    int errorCode = initialize();

    if (errorCode == 0) {
        m_manager.start();
    }

    return errorCode;
}

int Game::Engine::initialize() {
    sf::RenderWindow& window = m_manager.getWindow();

    window.create(sf::VideoMode(600, 600), "Game of Life", sf::Style::Close);
    window.setKeyRepeatEnabled(false);
    m_manager.setScene(std::make_unique<Scenes::GameScene>(m_manager));

    return 0;
}
