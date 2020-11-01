#include <catch2/catch.hpp>

#include "core/widgets/Widget.h"
#include "core/widgets/Button.h"
#include "core/widgets/VerticalLayout.h"
#include "core/widgets/HorizontalLayout.h"
#include "../TestsUtils.h"
#include <memory>

TEST_CASE("[Widget]")
{
	std::unique_ptr<ire::core::widgets::Widget> widgetPtr =
		ire::core::widgets::Button::create();
	SECTION("Name")
	{
		widgetPtr->setWidgetName("Tomek");
		REQUIRE(widgetPtr->getWidgetName() == std::string("Tomek"));

		std::unique_ptr<ire::core::widgets::Widget> widget2Ptr = 
			ire::core::widgets::Button::create();
		widget2Ptr = std::move(widgetPtr);
		REQUIRE(widget2Ptr->getWidgetName() == std::string("Tomek"));
	}
	SECTION("Position")
	{
		widgetPtr->setPosition({ 40, 60 });
		REQUIRE(areAlmostEqual(widgetPtr->getPosition(), sf::Vector2f(40, 60)));

		std::unique_ptr<ire::core::widgets::Widget> widget2Ptr = 
			ire::core::widgets::Button::create();
		widget2Ptr = std::move(widgetPtr);
		REQUIRE(areAlmostEqual(widget2Ptr->getPosition(), sf::Vector2f(40, 60)));

	}
	SECTION("Size")
	{
		widgetPtr->setSize({ 100, 100 });
		REQUIRE(areAlmostEqual(widgetPtr->getSize(), sf::Vector2f(100, 100)));

		widgetPtr->setWidth(50);
		REQUIRE(areAlmostEqual(widgetPtr->getSize(), sf::Vector2f(50, 100)));

		widgetPtr->setHeight(50);
		REQUIRE(areAlmostEqual(widgetPtr->getSize(), sf::Vector2f(50, 50)));

		std::unique_ptr<ire::core::widgets::Widget> widget2Ptr =
			std::make_unique<ire::core::widgets::Button>();
		widget2Ptr = std::move(widgetPtr);
		REQUIRE(areAlmostEqual(widget2Ptr->getSize(), sf::Vector2f(50, 50)));
	}
	SECTION("Origin")
	{
		widgetPtr->setOrigin({ 0, 10 });
		REQUIRE(areAlmostEqual(widgetPtr->getOrigin(), sf::Vector2f(0, 10)));

		std::unique_ptr<ire::core::widgets::Widget> widget2Ptr = 
			ire::core::widgets::Button::create();
		widget2Ptr = std::move(widgetPtr);
		REQUIRE(widget2Ptr->getOrigin() == sf::Vector2f(0, 10));
	}
	SECTION("Parent")
	{
		std::unique_ptr<ire::core::widgets::VerticalLayout> vLayout =
			ire::core::widgets::VerticalLayout::create({ 100, 100 });

		vLayout->add(std::move(widgetPtr), "Widget");
		REQUIRE(vLayout->get("Widget")->getParent() == vLayout.get());

		std::unique_ptr<ire::core::widgets::HorizontalLayout> hLayout =
			ire::core::widgets::HorizontalLayout::create({ 100, 100 });

		std::unique_ptr<ire::core::widgets::Widget> widget2Ptr =
			ire::core::widgets::Button::create();
		hLayout->add(std::move(widget2Ptr), "Widget2");
		REQUIRE(hLayout->get("Widget2")->getParent() == hLayout.get());
	}
}