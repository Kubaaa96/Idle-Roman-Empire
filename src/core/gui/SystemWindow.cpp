#include "SystemWindow.h"

namespace ire::core::gui {

    [[nodiscard]] sf::RenderTarget& SystemWindow::getRenderTarget()
    {
        return m_window;
    }

    [[nodiscard]] bool SystemWindow::isOpen() const
    {
        return m_window.isOpen();
    }

    void SystemWindow::processEvents()
    {
        sf::Event ev;
        while (m_window.pollEvent(ev))
        {
            processSfmlEvent(ev);
        }
    }

    void SystemWindow::close()
    {
        m_window.close();
    }

    void SystemWindow::display()
    {
        m_window.display();
    }

    void SystemWindow::draw()
    {
        auto& renderTarget = getRenderTarget();

        renderTarget.clear();

        if (m_rootPanel)
        {
            m_rootPanel->draw(renderTarget);
        }
    }

    void SystemWindow::setRootPanel(Panel& panel)
    {
        m_rootPanel = &panel;
    }

    void SystemWindow::processSfmlEvent(sf::Event& ev)
    {
        switch (ev.type)
        {
        case sf::Event::EventType::Closed:
            processSfmlClosedEvent(ev);
            break;

        case sf::Event::EventType::MouseButtonPressed:
            processSfmlMouseButtonPressedEvent(ev);
        }
    }

    void SystemWindow::processSfmlClosedEvent(sf::Event& ev)
    {
        WindowClosedEvent translatedEv{};
        emitEvent<WindowClosedEvent>(translatedEv);

        if (!translatedEv.cancel)
        {
            close();
        }
    }

    void SystemWindow::processSfmlMouseButtonPressedEvent(sf::Event& ev)
    {
        MouseButtonDownEvent translatedEv{};
        translatedEv.button = ev.mouseButton.button;
        translatedEv.position = sf::Vector2f(
            static_cast<float>(ev.mouseButton.x), 
            static_cast<float>(ev.mouseButton.y));

        if (isOpen() && m_rootPanel != nullptr)
        {
            if (m_rootPanel->clientBounds().contains(translatedEv.position))
            {
                m_rootPanel->onEvent(translatedEv);
            }

            if (!translatedEv.handled)
            {
                emitEvent<MouseButtonDownEvent>(translatedEv);
            }
        }
    }

}