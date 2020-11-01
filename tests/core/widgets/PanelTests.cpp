#include <catch2/catch.hpp>

#include "core/gui/widgets/Panel.h"
#include "core/gui/widgets/VerticalLayout.h"
#include "core/gui/widgets/Button.h"

#include "../TestsUtils.h"

TEST_CASE("[Panel]")
{
	
	auto vLayout = ire::core::gui::VerticalLayout::create({ 200, 200 });

	auto button = ire::core::gui::Button::create();
	vLayout->add(std::move(button), "Button");
	auto button1 = ire::core::gui::Button::create();
	vLayout->add(std::move(button1), "Button1");

	auto panel = ire::core::gui::Panel::create({300, 300}, std::move(vLayout), "VerticalLayout");

	SECTION("WidgetType")
	{
		REQUIRE(panel->getType().getName() == "Panel");
	}
	SECTION("Background color and Outline ")
	{
		panel->setBackgroundColor(sf::Color::Magenta);
		REQUIRE(panel->getBackgroundColor() == sf::Color::Magenta);

		panel->setOutlineColor(sf::Color::Red);
		REQUIRE(panel->getOutlineColor() == sf::Color::Red);

		panel->setOutlineThickness(15);
		REQUIRE(panel->getOutlineThickness() == 15);
	}
	SECTION("Position and Size")
	{
		panel->setPosition({ 25, 50 });
		REQUIRE(areAlmostEqual(panel->getPosition(), sf::Vector2f({ 25, 50 })));
		REQUIRE(areAlmostEqual(panel->getLayout()->getPosition(), sf::Vector2f({ 25, 50 })));

		REQUIRE(areAlmostEqual(panel->getSize(), sf::Vector2f({ 300, 300 })));
		REQUIRE(areAlmostEqual(panel->getLayout()->getSize(), sf::Vector2f({ 300, 300 })));

		panel->setSize({ 250, 500 });
		REQUIRE(areAlmostEqual(panel->getSize(), sf::Vector2f({ 250, 500 })));
		REQUIRE(areAlmostEqual(panel->getLayout()->getSize(), sf::Vector2f({ 250, 500 })));

	}
}