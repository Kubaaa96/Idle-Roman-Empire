#include <catch2/catch.hpp>

#include "core/gui/widgets/Label.h"
//#include "core/gui/Text.h"

#include "TestsUtils.h"

TEST_CASE("[Label]")
{
	auto label = ire::core::gui::Label::create("Welcome");

	SECTION("WidgetType")
	{
		REQUIRE(label->getType().getName() == "Label");
	}
	SECTION("Name")
	{
		label->setWidgetName("Label1");
		REQUIRE(label->getWidgetName() == "Label1");
	}
	SECTION("PositionAndSize")
	{
		label->setPosition({ 40, 50 });
		label->setSize({ 100, 200 });

		REQUIRE(areAlmostEqual(label->getPosition(), sf::Vector2f({ 40, 50 })));
		REQUIRE(areAlmostEqual(label->getSize(), sf::Vector2f({ 100, 200 })));
	}
	SECTION("Text")
	{
		REQUIRE(label->getTextString() == "Welcome");
		label->setTextString("How can i live");
		REQUIRE(label->getTextString() == "How can i live");

		SECTION("CharacterSize")
		{
			REQUIRE(label->getCharacterSize() == 45);
			label->setCharacterSize(25);
			REQUIRE(label->getCharacterSize() == 25);
		}
		SECTION("VerticalAlignment")
		{
			REQUIRE(label->getVerticalAlignment() == ire::core::gui::Text::VerticalAlignment::Center);
			label->setVerticalAlignment(ire::core::gui::Text::VerticalAlignment::Bottom);
			REQUIRE(label->getVerticalAlignment() == ire::core::gui::Text::VerticalAlignment::Bottom);
		}
		SECTION("HorizontalAlignment")
		{
			REQUIRE(label->getHorizontalAlignment() == ire::core::gui::Text::HorizontalAlignment::Center);
			label->setHorizontalAlignment(ire::core::gui::Text::HorizontalAlignment::Left);
			REQUIRE(label->getHorizontalAlignment() == ire::core::gui::Text::HorizontalAlignment::Left);
		}
		SECTION("Visibility")
		{
			REQUIRE(label->isTextVisible() == true);
			label->setTextVisible(false);
			REQUIRE(label->isTextVisible() == false);
		}
		SECTION("FillColor")
		{
			REQUIRE(label->getTextFillColor() == sf::Color::White);
			label->setTextFillColor(sf::Color::Magenta);
			REQUIRE(label->getTextFillColor() == sf::Color::Magenta);
		}
		SECTION("OutlineColor")
		{
			label->setTextOutlineColor(sf::Color::Red);
			REQUIRE(label->getTextOutlineColor() == sf::Color::Red);
		}
		SECTION("OutlineThickness")
		{
			label->setTextOutlineThickness(2);
			REQUIRE(label->getTextOutlineThickness() == 2);
		}
		
	}
	SECTION("BackgroundVisibility")
	{
		REQUIRE(label->isBackgroundVisible() == false);
		label->setBackgdoungVisibility(true);
		REQUIRE(label->isBackgroundVisible() == true);
	}
	SECTION("BackgroundFillColor")
	{
		REQUIRE(label->getBackgroundShapeColor() == sf::Color::Green);
		label->setBackgroundShapeColor(sf::Color::Red);
		REQUIRE(label->getBackgroundShapeColor() == sf::Color::Red);
	}
}