#include <catch2/catch.hpp>

#include <SFML/Window/Event.hpp>

#include "core/gui/Events.h"

#include <memory>

using namespace ire::core::gui;

namespace {

    struct MockedWidget : EventEmitter
    {
        virtual void onClick() = 0;
    };

    struct MockedButton : MockedWidget
    {
        void onClick() override
        {
            auto ev = MouseDownEvent{ {}, sf::Mouse::Button::Left, sf::Vector2f(123, 321) };
            emitEvent(ev);
        }
    };

}

TEST_CASE("Event emitter tests", "[events]")
{
    std::unique_ptr<MockedWidget> w = std::make_unique<MockedButton>();
    w->onClick();

    int counter = 0;

    auto wrongListener = [&counter](MouseUpEvent& ev) { ++counter; };
    auto rightListener = [&counter](MouseDownEvent& ev) { ++counter; };
    auto rightCancellingListener = [&counter](MouseDownEvent& ev) { ++counter; ev.handled = true; };

    w->addEventListener<MouseUpEvent>(wrongListener);
    w->onClick();
    REQUIRE(counter == 0);

    w->addEventListener<MouseDownEvent>(rightListener);
    w->onClick();
    REQUIRE(counter == 1);
    w->onClick();
    REQUIRE(counter == 2);

    w->addEventListener<MouseDownEvent>(rightListener);
    w->onClick();
    REQUIRE(counter == 4);

    w->addEventListener<MouseDownEvent>(rightCancellingListener);
    w->addEventListener<MouseDownEvent>(rightListener);
    w->onClick();
    REQUIRE(counter == 7);
}