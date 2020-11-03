#ifndef IRE_SYSTEM_WINDOW_H
#define IRE_SYSTEM_WINDOW_H

#include <SFML/Graphics.hpp>

#include "Events.h"

#include <utility>

namespace ire::core::gui {

    struct SystemWindow : EventEmitter
    {

        template <typename... Ts>
        SystemWindow(Ts&&... args) :
            m_window(std::forward<Ts>(args)...)
        {
        }

        [[nodiscard]] sf::RenderTarget& getRenderTarget();

        [[nodiscard]] bool isOpen() const;

        void processEvents();

        void close();

        void display();

    private:
        sf::RenderWindow m_window;

        void processSfmlEvent(sf::Event& ev);
    };

}

#endif // !IRE_SYSTEM_WINDOW_H
