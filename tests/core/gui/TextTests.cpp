#include <catch2/catch.hpp>
#include "core/gui/Text.h"

TEST_CASE("[Text]")
{
    ire::core::gui::Text text;
    SECTION("HorizontalAlignment")
    {
        REQUIRE(text.getHAlign() == ire::core::gui::Text::HorizontalAlignment::Center);
        text.setHAlign(ire::core::gui::Text::HorizontalAlignment::Left);
        REQUIRE(text.getHAlign() == ire::core::gui::Text::HorizontalAlignment::Left);

        REQUIRE(text.m_isHAlign == true);
        text.m_isHAlign = false;
        REQUIRE(text.m_isHAlign == false);
    }
    SECTION("VerticalAlignment")
    {
        REQUIRE(text.getVAlign() == ire::core::gui::Text::VerticalAlignment::Center);
        text.setVAlign(ire::core::gui::Text::VerticalAlignment::Bottom);
        REQUIRE(text.getVAlign() == ire::core::gui::Text::VerticalAlignment::Bottom);
        REQUIRE(text.m_isVAlign == true);
        text.m_isVAlign = false;
        REQUIRE(text.m_isVAlign == false);
    }
    SECTION("Visibilitty")
    {
        REQUIRE(text.getVisibility() == false);
        text.setVisibility(true);
        REQUIRE(text.getVisibility() == true);
    }
}