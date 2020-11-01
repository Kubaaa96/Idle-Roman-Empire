#include <catch2/catch.hpp>

#include "core/widgets/VerticalLayout.h"
#include "core/widgets/Button.h"
#include "../TestsUtils.h"
TEST_CASE("[VerticalLayout]")
{
	auto layout = ire::core::widgets::VerticalLayout::create({ 100,100 });
	layout->setSize({ 500, 400 });
	layout->setOrigin({ 0, 0 });
	layout->setLocalPosition({ 50, 50 });
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

			REQUIRE(areAlmostEqual(layout->get("Button1")->getPosition(), sf::Vector2f({ 50, 50 })));
			REQUIRE(areAlmostEqual(layout->get("Button1")->getSize(), sf::Vector2f({ 500,400 })));

			auto button2 = ire::core::widgets::Button::create();
			layout->add(std::move(button2), "Button2");

			REQUIRE(areAlmostEqual(layout->get("Button2")->getPosition(), sf::Vector2f({ 50, 250 })));
			REQUIRE(areAlmostEqual(layout->get("Button2")->getSize(), sf::Vector2f({ 500,200 })));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			auto button4 = ire::core::widgets::Button::create();
			layout->add(std::move(button4), "Button4");

			REQUIRE(areAlmostEqual(layout->get("Button3")->getPosition(), sf::Vector2f({ 50, 250 })));
			REQUIRE(areAlmostEqual(layout->get("Button3")->getSize(), sf::Vector2f({ 500, 100 })));

			REQUIRE(areAlmostEqual(layout->get("Button4")->getPosition(), sf::Vector2f({ 50, 350 })));
			REQUIRE(areAlmostEqual(layout->get("Button4")->getSize(), sf::Vector2f({ 500, 100 })));
		}
		SECTION("With Spacing without margins")
		{
			layout->setSpaces(4);
			auto button1 = ire::core::widgets::Button::create();
			layout->add(std::move(button1), "Button1");

			REQUIRE(areAlmostEqual(layout->get("Button1")->getPosition(), sf::Vector2f({ 50, 50 })));
			REQUIRE(areAlmostEqual(layout->get("Button1")->getSize(), sf::Vector2f({ 500,400 })));

			auto button2 = ire::core::widgets::Button::create();
			layout->add(std::move(button2), "Button2");

			REQUIRE(areAlmostEqual(layout->get("Button2")->getPosition(), sf::Vector2f({ 50, 252 })));
			REQUIRE(areAlmostEqual(layout->get("Button2")->getSize(), sf::Vector2f({ 500,198 })));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			auto button4 = ire::core::widgets::Button::create();
			layout->add(std::move(button4), "Button4");

			REQUIRE(areAlmostEqual(layout->get("Button3")->getPosition(), sf::Vector2f({ 50, 252 })));
			REQUIRE(areAlmostEqual(layout->get("Button3")->getSize(), sf::Vector2f({ 500, 97 })));

			REQUIRE(areAlmostEqual(layout->get("Button4")->getPosition(), sf::Vector2f({ 50, 353 })));
			REQUIRE(areAlmostEqual(layout->get("Button4")->getSize(), sf::Vector2f({ 500, 97 })));

		}
		SECTION("Without Spacing With Margins")
		{
			layout->setMargins({ 4, 4, 8, 8 });
			layout->setSpaces(0);
			auto button1 = ire::core::widgets::Button::create();
			layout->add(std::move(button1), "Button1");

			REQUIRE(areAlmostEqual(layout->get("Button1")->getPosition(), sf::Vector2f({ 54, 58 })));
			REQUIRE(areAlmostEqual(layout->get("Button1")->getSize(), sf::Vector2f({ 492, 384 })));

			auto button2 = ire::core::widgets::Button::create();
			layout->add(std::move(button2), "Button2");

			REQUIRE(areAlmostEqual(layout->get("Button2")->getPosition(), sf::Vector2f({ 54, 250 })));
			REQUIRE(areAlmostEqual(layout->get("Button2")->getSize(), sf::Vector2f({ 492, 192 })));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			auto button4 = ire::core::widgets::Button::create();
			layout->add(std::move(button4), "Button4");

			REQUIRE(areAlmostEqual(layout->get("Button3")->getPosition(), sf::Vector2f({ 54, 250 })));
			REQUIRE(areAlmostEqual(layout->get("Button3")->getSize(), sf::Vector2f({ 492, 96 })));

			REQUIRE(areAlmostEqual(layout->get("Button4")->getPosition(), sf::Vector2f({ 54, 346 })));
			REQUIRE(areAlmostEqual(layout->get("Button4")->getSize(), sf::Vector2f({ 492, 96 })));

		}
		SECTION("With Spacing With Margins")
		{
			layout->setMargins({ 4, 4, 5, 5 });
			layout->setSpaces(2);
			auto button1 = ire::core::widgets::Button::create();
			layout->add(std::move(button1), "Button1");

			REQUIRE(areAlmostEqual(layout->get("Button1")->getPosition(), sf::Vector2f({ 54, 55 })));
			REQUIRE(areAlmostEqual(layout->get("Button1")->getSize(), sf::Vector2f({ 492, 390 })));

			auto button2 = ire::core::widgets::Button::create();
			layout->add(std::move(button2), "Button2");

			REQUIRE(areAlmostEqual(layout->get("Button2")->getPosition(), sf::Vector2f({ 54, 251 })));
			REQUIRE(areAlmostEqual(layout->get("Button2")->getSize(), sf::Vector2f({ 492,194 })));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			auto button4 = ire::core::widgets::Button::create();
			layout->add(std::move(button4), "Button4");

			REQUIRE(areAlmostEqual(layout->get("Button3")->getPosition(), sf::Vector2f({ 54, 251 })));
			REQUIRE(areAlmostEqual(layout->get("Button3")->getSize(), sf::Vector2f({ 492, 96 })));

			REQUIRE(areAlmostEqual(layout->get("Button4")->getPosition(), sf::Vector2f({ 54, 349 })));
			REQUIRE(areAlmostEqual(layout->get("Button4")->getSize(), sf::Vector2f({ 492, 96 })));

		}
	}
	SECTION("Layout Stretch")
	{
		layout->setSize({ 500, 1000 });
		SECTION("Without margins and spacing")
		{
			layout->setSpaces(0);
			layout->setMargins({ 0, 0, 0, 0 });

			auto button1 = ire::core::widgets::Button::create();
			layout->add(std::move(button1), "Button1");
			auto button2 = ire::core::widgets::Button::create();
			layout->add(std::move(button2), "Button2");

			layout->setLayoutStretch({ 1,2 });
			REQUIRE(areAlmostEqual(layout->get("Button1")->getPosition(), sf::Vector2f({ 50 ,50 })));
			REQUIRE(areAlmostEqual(layout->get("Button1")->getSize(), sf::Vector2f({ 500 ,333 })));

			REQUIRE(areAlmostEqual(layout->get("Button2")->getPosition(), sf::Vector2f({ 50 ,383 })));
			REQUIRE(areAlmostEqual(layout->get("Button2")->getSize(), sf::Vector2f({ 500 ,667 })));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			layout->setLayoutStretch({ 1, 2, 1 });
			REQUIRE(areAlmostEqual(layout->get("Button3")->getPosition(), sf::Vector2f({ 50 ,800 })));
			REQUIRE(areAlmostEqual(layout->get("Button3")->getSize(), sf::Vector2f({ 500 ,250 })));

		}
		SECTION("With margins and without spacing")
		{
			layout->setSpaces(0);
			layout->setMargins({ 5, 5, 6, 6});

			auto button1 = ire::core::widgets::Button::create();
			layout->add(std::move(button1), "Button1");
			auto button2 = ire::core::widgets::Button::create();
			layout->add(std::move(button2), "Button2");

			layout->setLayoutStretch({ 1,2 });
			REQUIRE(areAlmostEqual(layout->get("Button1")->getPosition(), sf::Vector2f({ 55 , 56 })));
			REQUIRE(areAlmostEqual(layout->get("Button1")->getSize(), sf::Vector2f({ 489 ,329 })));
			
			REQUIRE(areAlmostEqual(layout->get("Button2")->getPosition(), sf::Vector2f({ 55 ,386 })));
			REQUIRE(areAlmostEqual(layout->get("Button2")->getSize(), sf::Vector2f({ 490 ,659 })));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			layout->setLayoutStretch({ 1, 2, 1 });
			REQUIRE(areAlmostEqual(layout->get("Button3")->getPosition(), sf::Vector2f({ 55 ,798 })));
			REQUIRE(areAlmostEqual(layout->get("Button3")->getSize(), sf::Vector2f({ 490 ,246 })));
		}
		SECTION("Without margins and witgh spacing")
		{
			layout->setSpaces(5);
			layout->setMargins({ 0, 0, 0, 0 });

			auto button1 = ire::core::widgets::Button::create();
			layout->add(std::move(button1), "Button1");
			auto button2 = ire::core::widgets::Button::create();
			layout->add(std::move(button2), "Button2");

			layout->setLayoutStretch({ 1,2 });
			REQUIRE(areAlmostEqual(layout->get("Button1")->getPosition(), sf::Vector2f({ 50 ,50 })));
			REQUIRE(areAlmostEqual(layout->get("Button1")->getSize(), sf::Vector2f({ 500 ,332 })));
			REQUIRE(areAlmostEqual(layout->get("Button2")->getPosition(), sf::Vector2f({ 50 ,387 })));
			REQUIRE(areAlmostEqual(layout->get("Button2")->getSize(), sf::Vector2f({ 500 ,663 })));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			layout->setLayoutStretch({ 1, 2, 1 });
			REQUIRE(areAlmostEqual(layout->get("Button3")->getPosition(), sf::Vector2f({ 50 ,803 })));
			REQUIRE(areAlmostEqual(layout->get("Button3")->getSize(), sf::Vector2f({ 500 ,247 })));
		}
		SECTION("With margins and spacing")
		{
			layout->setSpaces(5);
			layout->setMargins({ 5, 5, 5, 5 });

			auto button1 = ire::core::widgets::Button::create();
			layout->add(std::move(button1), "Button1");
			auto button2 = ire::core::widgets::Button::create();
			layout->add(std::move(button2), "Button2");

			layout->setLayoutStretch({ 1,2 });
			REQUIRE(areAlmostEqual(layout->get("Button1")->getPosition(), sf::Vector2f({ 55 ,55 })));
			REQUIRE(areAlmostEqual(layout->get("Button1")->getSize(), sf::Vector2f({ 490 ,328 })));

			REQUIRE(areAlmostEqual(layout->get("Button2")->getPosition(), sf::Vector2f({ 55 ,388 })));
			REQUIRE(areAlmostEqual(layout->get("Button2")->getSize(), sf::Vector2f({ 490 , 657 })));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			layout->setLayoutStretch({ 1, 2, 1 });
			REQUIRE(areAlmostEqual(layout->get("Button3")->getPosition(), sf::Vector2f({ 55 ,800 })));
			REQUIRE(areAlmostEqual(layout->get("Button3")->getSize(), sf::Vector2f({ 490 ,245 })));
		}
	}
	SECTION("Spaces")
	{
		REQUIRE(layout->getSpaces() == 1);

		layout->setSpaces(5);
		REQUIRE(layout->getSpaces() == 5);
	}
}