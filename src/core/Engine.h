#ifndef ENGINE_H
#define ENGINE_H

#include "gui/SystemWindow.h"

#include <memory>

namespace ire::core {

    struct Engine {
        Engine(gui::SystemWindow& window);

        void run();

    private:
        gui::SystemWindow& m_window;
    };

}

#endif // !ENGINE_H
