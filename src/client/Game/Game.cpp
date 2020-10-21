#include <iostream>

#include "Game.h"

Game& Game::instance()
{
    static Game game;
    return game;
}
void Game::run()
{
    m_engine.run();
}

Game::Game()
    : m_window(sf::VideoMode(m_windowWidth, m_windowHeight), "Idle Roman Empire")
    , m_engine(m_window)
{
}
