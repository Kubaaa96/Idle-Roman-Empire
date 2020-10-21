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

sf::RenderWindow& Game::getWindow()
{
    return m_window;
}

const sf::RenderWindow& Game::getWindow() const
{
    return m_window;
}

ireEngine::Engine& Game::getEngine()
{
    return m_engine;
}

const ireEngine::Engine& Game::getEngine() const
{
    return m_engine;
}

Game::Game()
    : m_window(sf::VideoMode(m_windowWidth, m_windowHeight), "Idle Roman Empire")
    , m_engine(m_window)
{
}