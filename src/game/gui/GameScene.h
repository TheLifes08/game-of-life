#ifndef GAME_SCENES_GAME_SCENE_H
#define GAME_SCENES_GAME_SCENE_H

#include "Scene.h"
#include "../common/Field.h"


namespace Game {
    namespace Scenes {
        class GameScene : public Game::Gui::Scene {
        public:
            explicit GameScene(Gui::WindowManager& manager);

            void onEvent(const sf::Event& event) override;
            void onUpdate(const sf::Time& elapsedTime) override;

        private:
            void drawField();
            void nextGeneration();

            Common::Field m_field;
        };
    }
}


#endif // GAME_SCENES_GAME_SCENE_H
