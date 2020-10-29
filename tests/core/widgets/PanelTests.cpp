#include <catch2/catch.hpp>

#include "core/widgets/Panel.h"
#include "core/widgets/VerticalLayout.h"
#include "core/widgets/Button.h"

TEST_CASE("[Panel]")
{
	
	auto vLayout = ire::core::widgets::VerticalLayout::create({ 200, 200 });

	auto button = ire::core::widgets::Button::create();
	vLayout->add(std::move(button), "Button");
	auto button1 = ire::core::widgets::Button::create();
	vLayout->add(std::move(button1), "Button1");

	auto panel = ire::core::widgets::Panel::create({300, 300}, std::move(vLayout), "VerticalLayout");

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
		REQUIRE(panel->getPosition() == sf::Vector2f({ 25, 50 }));
		REQUIRE(panel->getLayout()->getPosition() == sf::Vector2f({ 25, 50 }));

		REQUIRE(panel->getSize() == sf::Vector2f({ 300, 300 }));
		REQUIRE(panel->getLayout()->getSize() == sf::Vector2f({ 300, 300 }));

		panel->setSize({ 250, 500 });
		REQUIRE(panel->getSize() == sf::Vector2f({ 250, 500 }));
		REQUIRE(panel->getLayout()->getSize() == sf::Vector2f({ 250, 500 }));

	}
}