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
				REQUIRE(button->getVAlignment() == ire::core::gui::Text::VerticalAlignment::Center);
				button->setVAlignment(ire::core::gui::Text::VerticalAlignment::Bottom);
				REQUIRE(button->getVAlignment() == ire::core::gui::Text::VerticalAlignment::Bottom);
			}
			SECTION("Horizontal")
			{
				REQUIRE(button->getHAlignment() == ire::core::gui::Text::HorizontalAlignment::Center);
				button->setHAlignment(ire::core::gui::Text::HorizontalAlignment::Left);
				REQUIRE(button->getHAlignment() == ire::core::gui::Text::HorizontalAlignment::Left);
			}
			button->setAlignment(ire::core::gui::Text::VerticalAlignment::Top, ire::core::gui::Text::HorizontalAlignment::Right);
			REQUIRE(button->getVAlignment() == ire::core::gui::Text::VerticalAlignment::Top);
			REQUIRE(button->getHAlignment() == ire::core::gui::Text::HorizontalAlignment::Right);
		}
	}
}