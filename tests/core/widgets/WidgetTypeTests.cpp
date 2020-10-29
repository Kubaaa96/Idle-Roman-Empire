#include <catch2/catch.hpp>
#include "core/widgets/WidgetType.h"
#include "core/widgets/Button.h"
#include "core/widgets/EditBox.h"

TEST_CASE("[WidgetType]")
{
	auto button = ire::core::widgets::Button::create();
	auto editBox = ire::core::widgets::EditBox::create();

	SECTION("Index")
	{
		REQUIRE(button->getType().getIndex() == 0);
		REQUIRE(editBox->getType().getIndex() == 0);
	}
	SECTION("Name")
	{
		REQUIRE(button->getType().getName() == "Button");
		REQUIRE(editBox->getType().getName() == "EditBox");
	}
}

