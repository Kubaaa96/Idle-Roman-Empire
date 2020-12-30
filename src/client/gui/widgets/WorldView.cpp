#include "WorldView.h"

#include "core/world/tiled_top_down/TiledTopDownSurface.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace ire::client::gui
{

    const WidgetType WorldView::m_type = WidgetType::create<WorldView>("WorldView");

    WorldView::WorldView(ire::core::world::World& world) :
        m_world(&world),
        m_state(State::Inactive)
    {
    }

    std::unique_ptr<WorldView> WorldView::create(ire::core::world::World& world)
    {
        auto widget = std::make_unique<WorldView>(world);
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

    void WorldView::onStoppedBeingActive()
    {
        m_state = State::Inactive;
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