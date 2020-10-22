#include <catch2/catch.hpp>

#include "core/widgets/Widget.h"
#include <memory>

TEST_CASE("[Widget]")
{
	std::unique_ptr<ire::core::widgets::Widget> widgetPtr = std::make_unique<ire::core::widgets::Widget>();
	SECTION("Name")
	{
		widgetPtr->setWidgetName("Tomek");
		REQUIRE(widgetPtr->getWidgetName() == std::string("Tomek"));

		std::unique_ptr<ire::core::widgets::Widget> widget2Ptr = std::make_unique<ire::core::widgets::Widget>();
		widget2Ptr = std::move(widgetPtr);
		REQUIRE(widget2Ptr->getWidgetName() == std::string("Tomek"));
	}
	SECTION("Position")
	{
		widgetPtr->setPosition(40, 60);
		REQUIRE(widgetPtr->getPosition() == sf::Vector2f(40, 60));

		std::unique_ptr<ire::core::widgets::Widget> widget2Ptr = std::make_unique<ire::core::widgets::Widget>();
		widget2Ptr = std::move(widgetPtr);
		REQUIRE(widget2Ptr->getPosition() == sf::Vector2f(40, 60));

	}
	SECTION("Size")
	{
		widgetPtr->setSize(100, 100);
		REQUIRE(widgetPtr->getSize() == sf::Vector2f(100, 100));

		widgetPtr->setWidth(50);
		REQUIRE(widgetPtr->getSize() == sf::Vector2f(50, 100));

		widgetPtr->setHeigh(50);
		REQUIRE(widgetPtr->getSize() == sf::Vector2f(50, 50));

		std::unique_ptr<ire::core::widgets::Widget> widget2Ptr = std::make_unique<ire::core::widgets::Widget>();
		widget2Ptr = std::move(widgetPtr);
		REQUIRE(widget2Ptr->getSize() == sf::Vector2f(50, 50));
	}
	SECTION("Origin")
	{
		widgetPtr->setOrigin(0, 10);
		REQUIRE(widgetPtr->getOrigin() == sf::Vector2f(0, 10));

		std::unique_ptr<ire::core::widgets::Widget> widget2Ptr = std::make_unique<ire::core::widgets::Widget>();
		widget2Ptr = std::move(widgetPtr);
		REQUIRE(widget2Ptr->getOrigin() == sf::Vector2f(0, 10));
	}
}