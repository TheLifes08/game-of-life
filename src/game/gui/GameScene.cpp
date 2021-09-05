#include "GameScene.h"
#include "WindowManager.h"

Game::Scenes::GameScene::GameScene(Game::Gui::WindowManager &manager)
: Scene(manager), m_field({216, 294}) {
    auto createPlaner = [this](long long x, long long y) {
        m_field.get({x - 1, y + 1}).state = Common::Cell::ALIVE;
        m_field.get({x, y + 1}).state = Common::Cell::ALIVE;
        m_field.get({x + 1, y + 1}).state = Common::Cell::ALIVE;
        m_field.get({x + 1, y}).state = Common::Cell::ALIVE;
        m_field.get({x, y - 1}).state = Common::Cell::ALIVE;
    };

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

    loadFromFile("../resources/map.png");
}

void Game::Scenes::GameScene::onEvent(const sf::Event& event) {

}

void Game::Scenes::GameScene::onUpdate(const sf::Time& elapsedTime) {
    static double frameTime = 0.0;

    frameTime += elapsedTime.asSeconds();

    if (frameTime > 0.1) {
        frameTime = 0.0;
        drawField();
        nextGeneration();
    }
}

void Game::Scenes::GameScene::drawField() {
    sf::RenderWindow& window = m_manager.getWindow();
    float rectangleSizeX = static_cast<float>(window.getSize().x) / static_cast<float>(m_field.size().x);
    float rectangleSizeY = static_cast<float>(window.getSize().y) / static_cast<float>(m_field.size().y);
    sf::RectangleShape shape(sf::Vector2f(rectangleSizeX, rectangleSizeY));

    shape.setFillColor(sf::Color::Black);

    for (long long y = 0; y < m_field.size().y; ++y) {
        for (long long x = 0; x < m_field.size().x; ++x) {
            Common::Cell& cell = m_field.get({x, y});

            if (cell.state == Common::Cell::ALIVE) {
                shape.setFillColor(sf::Color::White);
            } else {
                shape.setFillColor(sf::Color::Black);
            }

            shape.setPosition(x * rectangleSizeX, y * rectangleSizeY);
            window.draw(shape);
        }
    }
}

void Game::Scenes::GameScene::nextGeneration() {
    Common::Field field(m_field);

    for (long long y = 0; y < field.size().y; ++y) {
        for (long long x = 0; x < field.size().x; ++x) {
            size_t aliveCells = 0;
            Common::Cell& cell = field.get({x, y});
            const std::vector<Common::Index> shifts = {{-1, -1}, { 0, -1}, { 1, -1},
                                                          {-1,  0},           { 1,  0},
                                                          {-1,  1}, { 0,  1}, { 1,  1}};

            for (auto& shift : shifts) {
                try {
                    if (m_field.get({x + shift.x, y + shift.y}).state == Common::Cell::ALIVE) {
                        ++aliveCells;
                    }
                } catch (...) {
                    // do nothing
                }
            }

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

    m_field = field;
}
