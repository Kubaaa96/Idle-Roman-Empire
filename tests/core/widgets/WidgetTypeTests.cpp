#include <catch2/catch.hpp>

#include "core/gui/widgets/WidgetType.h"
#include "core/gui/widgets/Button.h"
#include "core/gui/widgets/EditBox.h"

TEST_CASE("[WidgetType]")
{
	auto button = ire::core::gui::Button::create();
	auto editBox = ire::core::gui::EditBox::create();

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

