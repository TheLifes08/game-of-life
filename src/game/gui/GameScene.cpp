#include "GameScene.h"
#include "WindowManager.h"
#include <random>

Game::Scenes::GameScene::GameScene(Game::Gui::WindowManager &manager, size_t fieldX, size_t fieldY)
: Scene(manager), m_field({fieldX, fieldY}), m_speed(0.1), m_pause(false) {
    auto loadFromFile = [this](const std::string& path) {
        sf::Image image;
        image.loadFromFile(path);

        for (long long y = 0; y < m_field.size().y; ++y) {
            for (long long x = 0; x < m_field.size().x; ++x) {
                sf::Color pixel = image.getPixel(x, y);

                if (pixel == sf::Color::Black) {
                    m_field.get({x, y}).state = Common::Cell::ALIVE;
                }
            }
        }
    };
    // loadFromFile("../resources/map.png");

    // Generating random field
    std::random_device rd;

    for (long long y = 0; y < m_field.size().y; ++y) {
        for (long long x = 0; x < m_field.size().x; ++x) {
            bool isAlive = rd() % 2 == 1;
            m_field.get({x - 1, y + 1}).state = (isAlive)? Common::Cell::ALIVE : Common::Cell::DEAD;
        }
    }
}

void Game::Scenes::GameScene::onEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::P) {
            m_pause = !m_pause;
        } else if (event.key.code == sf::Keyboard::Q) {
            setSpeed(m_speed - 0.01);
        } else if (event.key.code == sf::Keyboard::E) {
            setSpeed(m_speed + 0.01);
        }
    }
}

void Game::Scenes::GameScene::onUpdate(const sf::Time& elapsedTime) {
    static double frameTime = 0.0;

    frameTime += elapsedTime.asSeconds();

    if (frameTime > m_speed) {
        frameTime = 0.0;

        if (!m_pause) {
            drawField();
            nextGeneration();
        }
    }
}

void Game::Scenes::GameScene::setSpeed(double value) {
    if (value < 0.01) {
        m_speed = 0.01;
    } else {
        m_speed = value;
    }
}

void Game::Scenes::GameScene::drawField() {
    sf::RenderWindow& window = m_manager.getWindow();
    float rectangleSizeX = static_cast<float>(window.getSize().x) / static_cast<float>(m_field.size().x);
    float rectangleSizeY = static_cast<float>(window.getSize().y) / static_cast<float>(m_field.size().y);
    sf::RectangleShape shape(sf::Vector2f(rectangleSizeX, rectangleSizeY));

    for (long long y = 0; y < m_field.size().y; ++y) {
        for (long long x = 0; x < m_field.size().x; ++x) {
            Common::Cell& cell = m_field.get({x, y});

            if (cell.state == Common::Cell::ALIVE) {
                shape.setFillColor(sf::Color::White);
            } else {
                shape.setFillColor(sf::Color::Black);
            }

            shape.setPosition(static_cast<float>(x) * rectangleSizeX, static_cast<float>(y) * rectangleSizeY);
            window.draw(shape);
        }
    }
}

void Game::Scenes::GameScene::nextGeneration() {
    Common::Field nextField(m_field);
    const std::vector<Common::Index> shifts = {{-1, -1}, { 0, -1}, { 1, -1},
                                               {-1,  0},           { 1,  0},
                                               {-1,  1}, { 0,  1}, { 1,  1}};

    for (long long y = 0; y < nextField.size().y; ++y) {
        for (long long x = 0; x < nextField.size().x; ++x) {
            size_t aliveCells = 0;
            Common::Cell& cell = nextField.get({x, y});

            // Checking neighbours
            for (auto& shift : shifts) {
                if (m_field.get({x + shift.x, y + shift.y}).state == Common::Cell::ALIVE) {
                    ++aliveCells;
                }
            }

            // Updating cell state
            if (cell.state == Common::Cell::ALIVE) {
                if (aliveCells != 2 && aliveCells != 3) {
                    cell.state = Common::Cell::DEAD;
                }
            } else {
                if (aliveCells == 3) {
                    cell.state = Common::Cell::ALIVE;
                }
            }
        }
    }

    m_field = std::move(nextField);
}
