#ifndef IRE_SYSTEM_WINDOW_H
#define IRE_SYSTEM_WINDOW_H

#include <SFML/Graphics.hpp>

#include "Events.h"
#include "EventRoot.h"

#include "widgets/Panel.h"

#include <utility>

namespace ire::core::gui {

    struct SystemWindow : EventEmitter, EventRoot
    {

        template <typename... Ts>
        SystemWindow(Ts&&... args) :
            m_window(std::forward<Ts>(args)...),
            m_rootPanel(nullptr),
            m_activeWidget(nullptr),
            m_lastMousePosition(-1, -1)
        {
        }

        SystemWindow(const SystemWindow&) = delete;
        SystemWindow(SystemWindow&&) = delete;

        SystemWindow& operator=(const SystemWindow&) = delete;
        SystemWindow& operator=(SystemWindow&&) = delete;

        virtual ~SystemWindow() = default;

        [[nodiscard]] sf::RenderTarget& getRenderTarget();

        [[nodiscard]] bool isOpen() const;

        void processEvents();

        void close();

        void display();

        void draw();

        void setRootPanel(Panel& panel);

        void setActiveWidget(Widget& widget) override;
        void resetActiveWidget(Widget& widget) override;

    private:
        sf::RenderWindow m_window;
        Panel* m_rootPanel;

        // The currently active widget receives all events regardless
        // of the position of the mouse, etc.
        Widget* m_activeWidget;

        // To limit the number of MouseMoved events we only emit them if the position
        // changed when rounded to the nearest integer.
        sf::Vector2i m_lastMousePosition;

        void processSfmlEvent(sf::Event& ev, TimePoint timestamp);

        void processSfmlClosedEvent(sf::Event& ev, TimePoint timestamp);

        void processSfmlMouseButtonPressedEvent(sf::Event& ev, TimePoint timestamp);
        void processSfmlMouseButtonReleasedEvent(sf::Event& ev, TimePoint timestamp);
        void processSfmlMouseMovedEvent(sf::Event& ev, TimePoint timestamp);

        void reemitLastMouseMoved();

        template <typename EventT>
        void forwardEventWithPosition(EventT& ev)
        {
            if (isOpen() && m_rootPanel != nullptr)
            {
                if (m_activeWidget != nullptr)
                {
                    m_activeWidget->onEvent(*this, ev);
                    if (ev.handled)
                    {
                        return;
                    }
                }

                if (m_rootPanel->clientBounds().contains(ev.position))
                {
                    m_rootPanel->onEvent(*this, ev);
                }

                emitEventIfNotHandled<EventT>(ev);
            }
        }
    };

}

#endif // !IRE_SYSTEM_WINDOW_H
