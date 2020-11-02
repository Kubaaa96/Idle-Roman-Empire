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
    int counter = 0;

    auto wrongListener = [&counter](MouseUpEvent& ev) { ++counter; };
    auto rightListener = [&counter](MouseDownEvent& ev) { ++counter; };
    auto rightCancellingListener = [&counter](MouseDownEvent& ev) { ++counter; ev.handled = true; };

    SECTION("With no listener")
    {
        counter = 0;
        std::unique_ptr<MockedWidget> widget = std::make_unique<MockedButton>();

        widget->emitMouseDownEvent();
        REQUIRE(counter == 0);
    }


    SECTION("With unmatching listener")
    {
        counter = 0;
        std::unique_ptr<MockedWidget> widget = std::make_unique<MockedButton>();

        widget->addEventListener<MouseUpEvent>(wrongListener);
        widget->emitMouseDownEvent();
        REQUIRE(counter == 0);
    }

    SECTION("With matching listener")
    {
        counter = 0;
        std::unique_ptr<MockedWidget> widget = std::make_unique<MockedButton>();

        widget->addEventListener<MouseDownEvent>(rightListener);
        widget->emitMouseDownEvent();
        REQUIRE(counter == 1);
        widget->emitMouseDownEvent();
        REQUIRE(counter == 2);
    }

    SECTION("With two listeners")
    {
        counter = 0;
        std::unique_ptr<MockedWidget> widget = std::make_unique<MockedButton>();

        widget->addEventListener<MouseDownEvent>(rightListener);
        widget->addEventListener<MouseDownEvent>(rightListener);
        widget->emitMouseDownEvent();
        REQUIRE(counter == 2);
    }

    SECTION("With immediately unsubscribed RAII listener")
    {
        counter = 0;
        std::unique_ptr<MockedWidget> widget = std::make_unique<MockedButton>();
        
        (void)widget->addTemporaryEventListener<MouseDownEvent>(rightListener);
        widget->emitMouseDownEvent();
        REQUIRE(counter == 0);
    }

    SECTION("With cancelling listener")
    {
        counter = 0;
        std::unique_ptr<MockedWidget> widget = std::make_unique<MockedButton>();

        widget->addEventListener<MouseDownEvent>(rightCancellingListener);
        widget->addEventListener<MouseDownEvent>(rightListener);
        widget->emitMouseDownEvent();
        REQUIRE(counter == 1);
    }

    SECTION("With manual unsubscribe")
    {
        counter = 0;
        std::unique_ptr<MockedWidget> widget = std::make_unique<MockedButton>();

        auto guard = widget->addTemporaryEventListener<MouseDownEvent>(rightListener);
        widget->emitMouseDownEvent();
        REQUIRE(counter == 1);
        guard.stopListening();
        widget->emitMouseDownEvent();
        REQUIRE(counter == 1);
    }

    SECTION("Unsubscribe cancelling listener")
    {
        counter = 0;
        std::unique_ptr<MockedWidget> widget = std::make_unique<MockedButton>();

        auto guard = widget->addTemporaryEventListener<MouseDownEvent>(rightCancellingListener);
        widget->addEventListener<MouseDownEvent>(rightListener);
        widget->addEventListener<MouseDownEvent>(rightListener);
        widget->addEventListener<MouseDownEvent>(rightListener);
        widget->emitMouseDownEvent();
        REQUIRE(counter == 1);
        guard.stopListening();
        widget->emitMouseDownEvent();
        REQUIRE(counter == 4);
    }
}