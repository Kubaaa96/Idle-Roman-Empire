#ifndef GAME_H
#define GAME_H

#include "../../core/Engine.h"
#include <SFML/Graphics.hpp>

struct Game {
    static Game& instance();

    void run();

    sf::RenderWindow& getWindow();
    const sf::RenderWindow& getWindow() const;
    ireEngine::Engine& getEngine();
    const ireEngine::Engine& getEngine() const;

private:
    Game();
    const unsigned int m_windowWidth { 1024 };
    const unsigned int m_windowHeight { 768 };
    sf::RenderWindow m_window;
    ireEngine::Engine m_engine;
};

#endif // GAME_H
