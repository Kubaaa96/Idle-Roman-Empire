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
        TimePoint timestamp = TimePoint::now();
        sf::Event ev;
        while (m_window.pollEvent(ev))
        {
            processSfmlEvent(ev, timestamp);
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

    void SystemWindow::processSfmlEvent(sf::Event& ev, TimePoint timestamp)
    {
        switch (ev.type)
        {
        case sf::Event::EventType::Closed:
            processSfmlClosedEvent(ev, timestamp);
            break;

        case sf::Event::EventType::MouseButtonPressed:
            processSfmlMouseButtonPressedEvent(ev, timestamp);
            break;

        case sf::Event::EventType::MouseButtonReleased:
            processSfmlMouseButtonReleasedEvent(ev, timestamp);
            break;

        case sf::Event::EventType::MouseMoved:
            processSfmlMouseMovedEvent(ev, timestamp);
            break;
        }
    }

    void SystemWindow::processSfmlClosedEvent(sf::Event& ev, TimePoint timestamp)
    {
        WindowClosedEvent translatedEv{};
        emitEvent<WindowClosedEvent>(translatedEv);

        if (!translatedEv.cancel)
        {
            close();
        }
    }

    void SystemWindow::processSfmlMouseButtonPressedEvent(sf::Event& ev, TimePoint timestamp)
    {
        MouseButtonDownEvent translatedEv{};
        translatedEv.timestamp = timestamp;
        translatedEv.button = ev.mouseButton.button;
        translatedEv.position = sf::Vector2f(
            static_cast<float>(ev.mouseButton.x), 
            static_cast<float>(ev.mouseButton.y));

        forwardEventWithPosition(translatedEv);
    }

    void SystemWindow::processSfmlMouseButtonReleasedEvent(sf::Event& ev, TimePoint timestamp)
    {
        MouseButtonUpEvent translatedEv{};
        translatedEv.timestamp = timestamp;
        translatedEv.button = ev.mouseButton.button;
        translatedEv.position = sf::Vector2f(
            static_cast<float>(ev.mouseButton.x),
            static_cast<float>(ev.mouseButton.y));

        forwardEventWithPosition(translatedEv);
    }

    void SystemWindow::processSfmlMouseMovedEvent(sf::Event& ev, TimePoint timestamp)
    {
        if (ev.mouseMove.x == m_lastMousePosition.x
            && ev.mouseMove.y == m_lastMousePosition.y)
        {
            // We prevent unneccesary MouseMoved events.
            return;
        }

        MouseMovedEvent translatedEv{};
        translatedEv.timestamp = timestamp;
        translatedEv.position = sf::Vector2f(
            static_cast<float>(ev.mouseMove.x),
            static_cast<float>(ev.mouseMove.y));
        m_lastMousePosition = { ev.mouseMove.x, ev.mouseMove.y };

        forwardEventWithPosition(translatedEv);
    }

    void SystemWindow::setActiveWidget(Widget& widget)
    {
        m_activeWidget = &widget;
    }

    void SystemWindow::resetActiveWidget()
    {
        m_activeWidget = nullptr;
    }

}