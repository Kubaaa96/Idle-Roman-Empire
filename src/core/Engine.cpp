#include "Engine.h"
#include <iostream>

namespace ire::core {

    Engine::Engine(gui::SystemWindow& window)
        : m_window(window)
    {
    }

    void Engine::run()
    {
        for(;;) 
        {
            m_window.processEvents();

            if (!m_window.isOpen())
            {
                break;
            }
            m_window.update();
            m_window.draw();
            m_window.display();
        }
    }

}
