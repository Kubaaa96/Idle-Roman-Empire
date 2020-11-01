#include <catch2/catch.hpp>

#include "core/gui/widgets/Button.h"

#include "../TestsUtils.h"

TEST_CASE("[Button]")
{
	auto button = ire::core::gui::Button::create();

	SECTION("WidgetType")
	{
		REQUIRE(button->getType().getName() == "Button");
	}
	SECTION("Name")
	{
		button->setWidgetName("Button1");
		REQUIRE(button->getWidgetName() == "Button1");
	}
	SECTION("Position and Size")
	{
		button->setPosition({ 40, 50 });
		button->setSize({ 100, 200 });

		REQUIRE(areAlmostEqual(button->getPosition(), sf::Vector2f({ 40, 50 })));
		REQUIRE(areAlmostEqual(button->getSize(), sf::Vector2f({ 100, 200 })));
	}
}