#pragma once

#include "core/gui/Events.h"
#include "core/gui/widgets/ClickableWidget.h"
#include "client/Game/Objects/ObjectManager.h"

#include "core/world/World.h"
#include <optional>
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

        WorldView(ire::core::world::World& world, objects::ObjectManager& objectMenager);

        static std::unique_ptr<WorldView> create(core::world::World& world, objects::ObjectManager& objectMenager);

        void draw(sf::RenderTarget& target);

        const WidgetType getType() const override;

        // Why the hell is this virtual?
        void updateWidget() override;

        void onEvent(core::gui::EventRoot& sender, core::gui::MouseButtonDownEvent& ev) override;
        void onEvent(core::gui::EventRoot& sender, core::gui::MouseButtonUpEvent& ev) override;
        void onEvent(core::gui::EventRoot& sender, core::gui::MouseMovedEvent& ev) override;
        const std::optional<sf::Vector2f> getMousePos() const;

        void onStoppedBeingActive() override;

        bool isMouseOnOverlappingWidget = false;

    protected:
        void onClick(core::gui::MouseButtonUpEvent& ev);


    private:
        ire::core::world::World* m_world;
        objects::ObjectManager* m_objectManager;
        State m_state;

        void updateCamera();

        std::optional<sf::Vector2f> m_mousePos;
    };

}
