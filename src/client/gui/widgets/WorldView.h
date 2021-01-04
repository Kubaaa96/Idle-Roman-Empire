#pragma once

#include "core/gui/Events.h"
#include "core/gui/widgets/ClickableWidget.h"

#include "core/world/World.h"

#include <memory>

namespace ire::client::gui
{

    struct WorldView : ire::core::gui::ClickableWidget
    {
    private:
        enum struct State
        {
            Inactive,
            Active
        };

        static const WidgetType m_type;

    public:

        WorldView(ire::core::world::World& world);

        static std::unique_ptr<WorldView> create(ire::core::world::World& world);

        void draw(sf::RenderTarget& target);

        const WidgetType getType() const override;

        // Why the hell is this virtual?
        void updateWidget() override;

        void onEvent(core::gui::EventRoot& sender, core::gui::MouseButtonDownEvent& ev) override;
        void onEvent(core::gui::EventRoot& sender, core::gui::MouseButtonUpEvent& ev) override;
        void onEvent(core::gui::EventRoot& sender, core::gui::MouseMovedEvent& ev) override;

        void onStoppedBeingActive() override;

    protected:
        void onClick(core::gui::MouseButtonUpEvent& ev);

    private:
        ire::core::world::World* m_world;
        State m_state;

        void updateCamera();
    };

}
