#ifndef GAME_H
#define GAME_H

#include "core/Engine.h"

#include "core/gui/SystemWindow.h"

namespace ire::client {

    struct Game {
        static Game& instance();

        void run();

        core::gui::SystemWindow& getWindow();
        const core::gui::SystemWindow& getWindow() const;
        core::Engine& getEngine();
        const core::Engine& getEngine() const;

    private:
        Game();
        const unsigned int m_windowWidth{ 1024 };
        const unsigned int m_windowHeight{ 768 };
        core::gui::SystemWindow m_window;
        core::Engine m_engine;
    };

}

#endif // GAME_H
