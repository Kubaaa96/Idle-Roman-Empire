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

    void SystemWindow::processSfmlEvent(sf::Event& ev)
    {
        if (ev.type == sf::Event::EventType::Closed)
        {
            WindowClosedEvent translatedEv{};
            emitEvent<WindowClosedEvent>(translatedEv);

            if (!translatedEv.cancel)
            {
                close();
            }
        }
    }

}