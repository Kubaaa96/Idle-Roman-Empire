#ifndef GAME_H
#define GAME_H

#include "../../core/Engine.h"
#include <SFML/Graphics.hpp>

namespace ire::client {

    struct Game {
        static Game& instance();

        void run();

        sf::RenderWindow& getWindow();
        const sf::RenderWindow& getWindow() const;
        core::Engine& getEngine();
        const core::Engine& getEngine() const;

    private:
        Game();
        const unsigned int m_windowWidth{ 1024 };
        const unsigned int m_windowHeight{ 768 };
        sf::RenderWindow m_window;
        core::Engine m_engine;
    };

}

#endif // GAME_H
