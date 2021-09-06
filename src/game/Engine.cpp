#include "Engine.h"
#include "gui/GameScene.h"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int Game::Engine::execute(int argc, char** argv) {
    int errorCode = initialize(argc, argv);

    if (errorCode == 0) {
        m_manager.start();
    }

    return errorCode;
}

int Game::Engine::initialize(int argc, char** argv) {
    sf::RenderWindow& window = m_manager.getWindow();

    // Option values
    long long fieldX = 300, fieldY = 300, windowX = 600, windowY = 600;

    // Option description
    po::options_description desc("Available options");
    desc.add_options()
    ("help,h", "Print help.")
    ("field-x,x", po::value<long long>(&fieldX)->default_value(300), "Set the field size on the X-axis.")
    ("field-y,y", po::value<long long>(&fieldY)->default_value(300), "Set the field size on the Y-axis.")
    ("window-width,w", po::value<long long>(&windowX)->default_value(600), "Set the window width.")
    ("window-height,h", po::value<long long>(&windowY)->default_value(600), "Set the window height.")
    ;

    // Parse command line args
    po::variables_map vm;

    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
    } catch(const std::exception& e) {
        std::cout << e.what() << "\n";
        std::cout << desc << "\n";
        return 1;
    }

    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    window.create(sf::VideoMode(windowX, windowY), "Game of Life", sf::Style::Close);
    window.setKeyRepeatEnabled(false);
    m_manager.setScene(std::make_unique<Scenes::GameScene>(m_manager, fieldX, fieldY));

    return 0;
}
