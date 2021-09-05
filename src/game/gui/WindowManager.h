#ifndef GAME_GUI_WINDOW_MANAGER_H
#define GAME_GUI_WINDOW_MANAGER_H

#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <memory>


namespace Game {
    namespace Gui {
        class WindowManager {
        public:
            WindowManager() = default;

            void setReplacementScene(std::unique_ptr<Scene>&& scene);
            void setScene(std::unique_ptr<Scene>&& scene);

            void start();
            sf::RenderWindow& getWindow();

        private:
            sf::RenderWindow m_window;
            std::unique_ptr<Scene> m_scene;
            std::unique_ptr<Scene> m_replacementScene;
        };
    }
}


#endif // GAME_GUI_WINDOW_MANAGER_H
