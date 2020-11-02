#include <catch2/catch.hpp>

#include <SFML/Window/Event.hpp>

#include "core/gui/Events.h"

#include <memory>

using namespace ire::core::gui;

namespace {

    struct MockedWidget : EventEmitter
    {
        virtual void emitMouseDownEvent() = 0;
    };

    struct MockedButton : MockedWidget
    {
        void emitMouseDownEvent() override
        {
            auto ev = MouseDownEvent{ {}, sf::Mouse::Button::Left, sf::Vector2f(123, 321) };
            emitEvent(ev);
        }
    };

}

TEST_CASE("Event emitter tests", "[events]")
{
    std::unique_ptr<MockedWidget> widget = std::make_unique<MockedButton>();
    widget->emitMouseDownEvent();

    int counter = 0;

    auto wrongListener = [&counter](MouseUpEvent& ev) { ++counter; };
    auto rightListener = [&counter](MouseDownEvent& ev) { ++counter; };
    auto rightCancellingListener = [&counter](MouseDownEvent& ev) { ++counter; ev.handled = true; };

    widget->addEventListener<MouseUpEvent>(wrongListener);
    widget->emitMouseDownEvent();
    REQUIRE(counter == 0);

    widget->addEventListener<MouseDownEvent>(rightListener);
    widget->emitMouseDownEvent();
    REQUIRE(counter == 1);
    widget->emitMouseDownEvent();
    REQUIRE(counter == 2);

    widget->addEventListener<MouseDownEvent>(rightListener);
    widget->emitMouseDownEvent();
    REQUIRE(counter == 4);

    (void)widget->addTemporaryEventListener<MouseDownEvent>(rightListener);
    widget->emitMouseDownEvent();
    REQUIRE(counter == 6);

    auto guard = widget->addTemporaryEventListener<MouseDownEvent>(rightCancellingListener);
    widget->addEventListener<MouseDownEvent>(rightListener);
    widget->emitMouseDownEvent();
    REQUIRE(counter == 9);

    guard = widget->addTemporaryEventListener<MouseDownEvent>(rightListener);
    widget->emitMouseDownEvent();
    REQUIRE(counter == 13);
    widget->emitMouseDownEvent();
    REQUIRE(counter == 17);
    guard.stopListening();
    widget->emitMouseDownEvent();
    REQUIRE(counter == 20);

    {
        auto guard = widget->addTemporaryEventListener<MouseDownEvent>(rightListener);
        widget->emitMouseDownEvent();
        REQUIRE(counter == 24);
    }
    widget->emitMouseDownEvent();
    REQUIRE(counter == 27);
}