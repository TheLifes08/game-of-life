#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "gui/WindowManager.h"


namespace Game {
    class Engine {
    public:
        Engine() = default;
        Engine(const Engine&) = delete;
        Engine(Engine&&) = delete;
        Engine& operator=(const Engine&) = delete;
        Engine& operator=(Engine&&) = delete;
        ~Engine() = default;

        virtual int initialize(int argc, char** argv);
        int execute(int argc, char** argv);

    protected:
        Gui::WindowManager m_manager;
    };
}


#endif // GAME_ENGINE_H
