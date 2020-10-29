#include <catch2/catch.hpp>

#include "core/widgets/VerticalLayout.h"
#include "core/widgets/Button.h"

TEST_CASE("[VerticalLayout]")
{
	auto layout = ire::core::widgets::VerticalLayout::create({ 100,100 });
	layout->setSize({ 500, 400});
	layout->setPosition({ 50, 50 });
	SECTION("WidgetType")
	{
		REQUIRE(layout->getType().getName() == "VerticalLayout");
	}
	SECTION("Position and Size")
	{
		SECTION("Without Spaces and margins")
		{
			layout->setSpaces(0);
			auto button1 = ire::core::widgets::Button::create();
			layout->add(std::move(button1), "Button1");

			REQUIRE(layout->get("Button1")->getPosition() == sf::Vector2f({ 50, 50 }));
			REQUIRE(layout->get("Button1")->getSize() == sf::Vector2f({ 500,400 }));

			auto button2 = ire::core::widgets::Button::create();
			layout->add(std::move(button2), "Button2");

			REQUIRE(layout->get("Button2")->getPosition() == sf::Vector2f({ 50, 250 }));
			REQUIRE(layout->get("Button2")->getSize() == sf::Vector2f({ 500,200 }));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			auto button4 = ire::core::widgets::Button::create();
			layout->add(std::move(button4), "Button4");

			REQUIRE(layout->get("Button3")->getPosition() == sf::Vector2f({ 50, 250 }));
			REQUIRE(layout->get("Button3")->getSize() == sf::Vector2f({ 500, 100 }));

			REQUIRE(layout->get("Button4")->getPosition() == sf::Vector2f({ 50, 350 }));
			REQUIRE(layout->get("Button4")->getSize() == sf::Vector2f({ 500, 100 }));
		}
		SECTION("With Spacing without margins")
		{
			layout->setSpaces(4);
			auto button1 = ire::core::widgets::Button::create();
			layout->add(std::move(button1), "Button1");

			REQUIRE(layout->get("Button1")->getPosition() == sf::Vector2f({ 50, 50 }));
			REQUIRE(layout->get("Button1")->getSize() == sf::Vector2f({ 500,400 }));

			auto button2 = ire::core::widgets::Button::create();
			layout->add(std::move(button2), "Button2");

			REQUIRE(layout->get("Button2")->getPosition() == sf::Vector2f({ 50, 252 }));
			REQUIRE(layout->get("Button2")->getSize() == sf::Vector2f({ 500,198 }));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			auto button4 = ire::core::widgets::Button::create();
			layout->add(std::move(button4), "Button4");

			REQUIRE(layout->get("Button3")->getPosition() == sf::Vector2f({ 50, 252 }));
			REQUIRE(layout->get("Button3")->getSize() == sf::Vector2f({ 500, 97 }));
			
			REQUIRE(layout->get("Button4")->getPosition() == sf::Vector2f({ 50, 353 }));
			REQUIRE(layout->get("Button4")->getSize() == sf::Vector2f({ 500, 97 }));

		}
		SECTION("Without Spacing With Margins")
		{
			layout->setMargins({4, 4, 8, 8});
			layout->setSpaces(0);
			auto button1 = ire::core::widgets::Button::create();
			layout->add(std::move(button1), "Button1");

			REQUIRE(layout->get("Button1")->getPosition() == sf::Vector2f({ 54, 58 }));
			REQUIRE(layout->get("Button1")->getSize() == sf::Vector2f({ 492, 384 }));

			auto button2 = ire::core::widgets::Button::create();
			layout->add(std::move(button2), "Button2");

			REQUIRE(layout->get("Button2")->getPosition() == sf::Vector2f({ 54, 250 }));
			REQUIRE(layout->get("Button2")->getSize() == sf::Vector2f({ 492, 192 }));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			auto button4 = ire::core::widgets::Button::create();
			layout->add(std::move(button4), "Button4");

			REQUIRE(layout->get("Button3")->getPosition() == sf::Vector2f({ 54, 250 }));
			REQUIRE(layout->get("Button3")->getSize() == sf::Vector2f({ 492, 96 }));

			REQUIRE(layout->get("Button4")->getPosition() == sf::Vector2f({ 54, 346 }));
			REQUIRE(layout->get("Button4")->getSize() == sf::Vector2f({ 492, 96 }));

		}
		SECTION("With Spacing With Margins")
		{
			layout->setMargins({ 4, 4, 5, 5 });
			layout->setSpaces(2);
			auto button1 = ire::core::widgets::Button::create();
			layout->add(std::move(button1), "Button1");

			REQUIRE(layout->get("Button1")->getPosition() == sf::Vector2f({ 54, 55 }));
			REQUIRE(layout->get("Button1")->getSize() == sf::Vector2f({ 492, 390}));

			auto button2 = ire::core::widgets::Button::create();
			layout->add(std::move(button2), "Button2");

			REQUIRE(layout->get("Button2")->getPosition() == sf::Vector2f({ 54, 251 }));
			REQUIRE(layout->get("Button2")->getSize() == sf::Vector2f({ 492,194 }));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			auto button4 = ire::core::widgets::Button::create();
			layout->add(std::move(button4), "Button4");

			REQUIRE(layout->get("Button3")->getPosition() == sf::Vector2f({ 54, 251 }));
			REQUIRE(layout->get("Button3")->getSize() == sf::Vector2f({ 492, 96 }));

			REQUIRE(layout->get("Button4")->getPosition() == sf::Vector2f({ 54, 349 }));
			REQUIRE(layout->get("Button4")->getSize() == sf::Vector2f({ 492, 96 }));

		}
	}
	SECTION("Spaces")
	{
		REQUIRE(layout->getSpaces() == 1);

		layout->setSpaces(5);
		REQUIRE(layout->getSpaces() == 5);
	}
}