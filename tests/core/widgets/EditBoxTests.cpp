#include <catch2/catch.hpp>

#include "core/gui/widgets/EditBox.h"

#include "../TestsUtils.h"

TEST_CASE("[EditBox]")
{
	auto editBox = ire::core::widgets::EditBox::create();

	SECTION("WidgetType")
	{
		REQUIRE(editBox->getType().getName() == "EditBox");
	}
	SECTION("Name")
	{
		editBox->setWidgetName("editBox1");
		REQUIRE(editBox->getWidgetName() == "editBox1");
	}
	SECTION("Position and Size")
	{
		editBox->setPosition({ 40, 50 });
		editBox->setSize({ 100, 200 });

		REQUIRE(areAlmostEqual(editBox->getPosition(), sf::Vector2f({ 40, 50 })));
		REQUIRE(areAlmostEqual(editBox->getSize(), sf::Vector2f({ 100, 200 })));
	}

}