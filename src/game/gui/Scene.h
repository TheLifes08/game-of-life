#ifndef GAME_GUI_SCENE_H
#define GAME_GUI_SCENE_H

#include <SFML/Graphics.hpp>


namespace Game {
    namespace Gui {
        class WindowManager;

        class Scene {
        public:
            explicit Scene(WindowManager& manager);

            virtual void onEvent(const sf::Event& event) = 0;
            virtual void onUpdate(const sf::Time& elapsedTime) = 0;

        protected:
            WindowManager& m_manager;
        };
    }
}


#endif // GAME_GUI_SCENE_H
