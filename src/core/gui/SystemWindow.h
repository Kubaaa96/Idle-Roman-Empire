#ifndef IRE_SYSTEM_WINDOW_H
#define IRE_SYSTEM_WINDOW_H

#include <SFML/Graphics.hpp>

#include "Events.h"

#include "widgets/Panel.h"

#include <utility>

namespace ire::core::gui {

    struct SystemWindow : EventEmitter
    {

        template <typename... Ts>
        SystemWindow(Ts&&... args) :
            m_window(std::forward<Ts>(args)...),
            m_rootPanel(nullptr)
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

    private:
        sf::RenderWindow m_window;
        Panel* m_rootPanel;

        void processSfmlEvent(sf::Event& ev);

        void processSfmlClosedEvent(sf::Event& ev);

        void processSfmlMouseButtonPressedEvent(sf::Event& ev);
    };

}

#endif // !IRE_SYSTEM_WINDOW_H
