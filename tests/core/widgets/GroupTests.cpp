#include <catch2/catch.hpp>

#include "core/widgets/Group.h"
#include "core/widgets/Button.h"
#include "../Testsutils.h"

TEST_CASE("[Group]")
{
	auto group = ire::core::widgets::Group::create({ 100, 100 });

	SECTION("WidgetType")
	{
		REQUIRE(group->getType().getName() == "Group");
	}
	SECTION("Position and Size")
	{
		group->setPosition({ 50, 20 });
		group->setSize({ 150, 150 });

		REQUIRE(group->getPosition() == sf::Vector2f({ 50, 20 }));
		REQUIRE(group->getSize() == sf::Vector2f({ 150, 150 }));
	}
	SECTION("ChildWidget")
	{		
		auto childWidget = ire::core::widgets::Button::create();
		childWidget->setPosition({ 100,100 });
		REQUIRE(areAlmostEqual<sf::Vector2f>(childWidget->getPosition(), sf::Vector2f({ 100, 100 })));
		group->add(std::move(childWidget), "ChildWidget");
		group->setPosition({ 0,0 });
		REQUIRE(areAlmostEqual<sf::Vector2f>(group->getWidgets()[0]->getPosition(), sf::Vector2f({ 100, 100 })));
		group->setPosition({100, 200});
		REQUIRE(areAlmostEqual<sf::Vector2f>(group->get("ChildWidget")->getPosition(), sf::Vector2f({ 200, 300 })));

		auto childWidget1 = ire::core::widgets::Button::create();
		group->add(std::move(childWidget1), "ChildWidget1");
		REQUIRE(areAlmostEqual<sf::Vector2f>(group->getWidgets()[1]->getPosition(), sf::Vector2f({ 100,200 })));
	}
}