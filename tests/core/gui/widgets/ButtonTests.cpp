#include <catch2/catch.hpp>

#include "core/gui/widgets/Button.h"

#include "TestsUtils.h"

TEST_CASE("[Button]")
{
	auto button = ire::core::gui::Button::create("Button");

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
	SECTION("Text")
	{
		REQUIRE(button->getTextString() == "Button");
		button->setTextString("Button1");
		REQUIRE(button->getTextString() == "Button1");
		SECTION("Character Size")
		{
			REQUIRE(button->getCharacterSize() == 30);
			button->setCharacterSize(25);
			REQUIRE(button->getCharacterSize() == 25);
		}
		SECTION("Style")
		{
			REQUIRE(button->getTextStyle() == sf::Text::Bold);
			button->setTextStyle(sf::Text::Bold | sf::Text::Underlined);
			REQUIRE(button->getTextStyle() == (sf::Text::Bold | sf::Text::Underlined));
		}
		SECTION("Fill Color")
		{
			REQUIRE(button->getTextFillColor() == sf::Color::White);
			button->setTextFillColor(sf::Color::Magenta);
			REQUIRE(button->getTextFillColor() == sf::Color::Magenta);	
		}
		SECTION("Alignment")
		{
			SECTION("Vertical")
			{
				REQUIRE(button->getVAlignment() == ire::core::gui::VAlign::Center);
				button->setVAlignment(ire::core::gui::VAlign::Left);
				REQUIRE(button->getVAlignment() == ire::core::gui::VAlign::Left);
			}
			SECTION("Horizontal")
			{
				REQUIRE(button->getHAlignment() == ire::core::gui::HAlign::Center);
				button->setHAlignment(ire::core::gui::HAlign::Bottom);
				REQUIRE(button->getHAlignment() == ire::core::gui::HAlign::Bottom);
			}
			button->setAlignment(ire::core::gui::VAlign::Right, ire::core::gui::HAlign::Top);
			REQUIRE(button->getVAlignment() == ire::core::gui::VAlign::Right);
			REQUIRE(button->getHAlignment() == ire::core::gui::HAlign::Top);
		}
	}
}