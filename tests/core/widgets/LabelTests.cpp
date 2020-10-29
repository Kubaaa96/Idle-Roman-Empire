#include <catch2/catch.hpp>
#include "core/widgets/Label.h"

TEST_CASE("[Label]")
{
	auto label = ire::core::widgets::Label::create();

	SECTION("WidgetType")
	{
		REQUIRE(label->getType().getName() == "Label");
	}
	SECTION("Name")
	{
		label->setWidgetName("Label1");
		REQUIRE(label->getWidgetName() == "Label1");
	}
	SECTION("Position and Size")
	{
		label->setPosition({ 40, 50 });
		label->setSize({ 100, 200 });

		REQUIRE(label->getPosition() == sf::Vector2f({ 40, 50 }));
		REQUIRE(label->getSize() == sf::Vector2f({ 100, 200 }));
	}

}