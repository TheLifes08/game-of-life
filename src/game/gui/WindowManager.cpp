#include "WindowManager.h"
#include <iostream>

void Game::Gui::WindowManager::setReplacementScene(std::unique_ptr<Scene>&& scene) {
    m_replacementScene = std::move(scene);
}

void Game::Gui::WindowManager::setScene(std::unique_ptr<Scene>&& scene) {
    m_scene = std::move(scene);
}

void Game::Gui::WindowManager::start() {
    sf::Clock clock;

    try {
        while (m_window.isOpen()) {
            sf::Event event {};

            // Check events
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    m_window.close();
                }

                if (m_scene != nullptr) {
                    m_scene->onEvent(event);
                }
            }

            // Change scene
            if (m_replacementScene != nullptr) {
                m_scene = std::move(m_replacementScene);
                m_replacementScene.reset();
            }

            // Draw scene
            if (m_scene != nullptr) {
                sf::Time elapsedTime = clock.getElapsedTime();
                clock.restart();
                m_scene->onUpdate(elapsedTime);
            }

            m_window.display();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return;
    } catch (...) {
        std::cerr << "Unknown error!\n";
        return;
    }
}

sf::RenderWindow& Game::Gui::WindowManager::getWindow() {
    return m_window;
}
