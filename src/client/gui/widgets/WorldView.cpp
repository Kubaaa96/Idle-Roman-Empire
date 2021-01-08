#include "WorldView.h"

#include "core/world/tiled_top_down/TiledTopDownSurface.h"
#include "core/world/tiled_top_down/TileOverlay.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace ire::client::gui
{

    const WidgetType WorldView::m_type = WidgetType::create<WorldView>("WorldView");

    WorldView::WorldView(ire::core::world::World& world, objects::ObjectMenager& objectMenager) :
        m_world(&world),
        m_objectMenager(&objectMenager),
        m_state(State::Inactive)
    {
    }

    std::unique_ptr<WorldView> WorldView::create(ire::core::world::World& world, objects::ObjectMenager& objectMenager)
    {
        auto widget = std::make_unique<WorldView>(world, objectMenager);
        return widget;
    }

    void WorldView::draw(sf::RenderTarget& target)
    {
        updateCamera();

        sf::RenderStates states = sf::RenderStates::Default;

        sf::View oldView = target.getView();
        sf::View view = oldView;

        view.setViewport(getClientViewport(target));
        target.setView(view);

        // TODO: Move this to some place where this actually should be managed from.
        //       Right now it's here for demo purposes.
        if (m_mousePos.has_value())
        {
            auto& mainSurface = static_cast<ire::core::world::TiledTopDownSurface&>(m_world->getMainSurface());
            auto pointedTilePos = mainSurface.mapClientToTilePosition(target, *m_mousePos);
            if (pointedTilePos.has_value())
            {
                if (!m_objectMenager->isCollectionOfBuildingsEmpty())
                {
                    mainSurface.setTileOverlays(m_objectMenager->getOverlayVector(*pointedTilePos));
                } 
            }
            else
            {
                mainSurface.resetTileOverlays();
            }
        }
        //

        sf::RectangleShape s;
        s.setFillColor(sf::Color::White);
        s.setSize(sf::Vector2f(10000.0f, 10000.0f));
        target.draw(s);

        m_world->getMainSurface().draw(target, states);

        target.setView(oldView);
    }

    const WidgetType WorldView::getType() const
    {
        return m_type;
    }

    // Why the hell is this virtual?
    void WorldView::updateWidget() {}

    void WorldView::onEvent(core::gui::EventRoot& sender, core::gui::MouseButtonDownEvent& ev)
    {

        m_state = State::Active;
        sender.setActiveWidget(*this);
        
        ev.handled = true;
    }

    void WorldView::onEvent(core::gui::EventRoot& sender, core::gui::MouseButtonUpEvent& ev)
    {
        if (m_state == State::Active && getClientBounds().contains(ev.position))
        {
            onClick(ev);
        }
        ev.handled = true;
    }

    void WorldView::onEvent(core::gui::EventRoot& sender, core::gui::MouseMovedEvent& ev)
    {
        if (getClientBounds().contains(ev.position))
        {
            m_mousePos = ev.position;
        }
        else
        {
            m_mousePos.reset();
        }
        emitEvent(ev);
        ev.handled = true;
    }

    const std::optional<sf::Vector2f> WorldView::getMousePos() const
    {
        return m_mousePos;
    }

    void WorldView::onStoppedBeingActive()
    {
        m_state = State::Inactive;
    }

    void WorldView::onClick(core::gui::MouseButtonUpEvent& ev)
    {
        core::gui::MouseClickEvent clickEv{};
        clickEv.timestamp = ev.timestamp;
        clickEv.button = ev.button;
        clickEv.position = ev.position;
        emitEvent<core::gui::MouseClickEvent>(clickEv);
    }

    void WorldView::updateCamera()
    {
        // TODO: replace later with event based and framerate agnostic implementation.
        //       Also, this should be handled in a different place and we should not assume the surface type.
        if (m_state != State::Active)
        {
            return;
        }

        auto& mainSurface = static_cast<ire::core::world::TiledTopDownSurface&>(m_world->getMainSurface());
        auto zoom = mainSurface.getZoom();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            mainSurface.moveCamera(sf::Vector2f(-1.0f, 0.0f) / zoom);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            mainSurface.moveCamera(sf::Vector2f(1.0f, 0.0f) / zoom);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            mainSurface.moveCamera(sf::Vector2f(0.0f, -1.0f) / zoom);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            mainSurface.moveCamera(sf::Vector2f(0.0f, 1.0f) / zoom);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
        {
            mainSurface.changeZoom(1.01f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
        {
            mainSurface.changeZoom(1 / 1.01f);
        }
    }
}
