#include <catch2/catch.hpp>
#include "core/gui/Text.h"

TEST_CASE("[Text]")
{
    ire::core::gui::Text text;
    SECTION("HorizontalAlignment")
    {
        REQUIRE(text.getHorizontalAlign() == ire::core::gui::Text::HorizontalAlignment::Center);
        text.setHorizontalAlign(ire::core::gui::Text::HorizontalAlignment::Left);
        REQUIRE(text.getHorizontalAlign() == ire::core::gui::Text::HorizontalAlignment::Left);
    }
    SECTION("VerticalAlignment")
    {
        REQUIRE(text.getVerticalAlign() == ire::core::gui::Text::VerticalAlignment::Center);
        text.setVerticalAlign(ire::core::gui::Text::VerticalAlignment::Bottom);
        REQUIRE(text.getVerticalAlign() == ire::core::gui::Text::VerticalAlignment::Bottom);
    }
    SECTION("Visibilitty")
    {
        REQUIRE(text.isVisible() == false);
        text.setVisible(true);
        REQUIRE(text.isVisible() == true);
    }
}