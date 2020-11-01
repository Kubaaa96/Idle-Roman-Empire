#include <catch2/catch.hpp>

#include "core/widgets/HorizontalLayout.h"
#include "core/widgets/Button.h"
#include "../TestsUtils.h"
TEST_CASE("[HorizontalLayout]")
{
	auto layout = ire::core::widgets::HorizontalLayout::create({ 100,100 });
	layout->setSize({ 500, 400 });
	layout->setPosition({ 50, 50 });
	SECTION("WidgetType")
	{
		REQUIRE(layout->getType().getName() == "HorizontalLayout");
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

			REQUIRE(areAlmostEqual(layout->get("Button2")->getPosition(), sf::Vector2f({ 300, 50 })));
			REQUIRE(areAlmostEqual(layout->get("Button2")->getSize(), sf::Vector2f({ 250, 400 })));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			auto button4 = ire::core::widgets::Button::create();
			layout->add(std::move(button4), "Button4");

			auto button5 = ire::core::widgets::Button::create();
			layout->add(std::move(button5), "Button5");

			REQUIRE(areAlmostEqual(layout->get("Button3")->getPosition(), sf::Vector2f({ 250, 50 })));
			REQUIRE(areAlmostEqual(layout->get("Button3")->getSize(), sf::Vector2f({ 100, 400 })));

			REQUIRE(areAlmostEqual(layout->get("Button4")->getPosition(), sf::Vector2f({ 350, 50 })));
			REQUIRE(areAlmostEqual(layout->get("Button4")->getSize(), sf::Vector2f({ 100, 400 })));

			REQUIRE(areAlmostEqual(layout->get("Button5")->getPosition(), sf::Vector2f({ 450, 50 })));
			REQUIRE(areAlmostEqual(layout->get("Button5")->getSize(), sf::Vector2f({ 100, 400 })));
		}
		SECTION("With Spacing without margins")
		{
			layout->setSpaces(5);
			auto button1 = ire::core::widgets::Button::create();
			layout->add(std::move(button1), "Button1");

			REQUIRE(areAlmostEqual(layout->get("Button1")->getPosition(), sf::Vector2f({ 50, 50 })));
			REQUIRE(areAlmostEqual(layout->get("Button1")->getSize(), sf::Vector2f({ 500, 400 })));

			auto button2 = ire::core::widgets::Button::create();
			layout->add(std::move(button2), "Button2");

			REQUIRE(areAlmostEqual(layout->get("Button2")->getPosition(), sf::Vector2f({ 302.5, 50 })));
			REQUIRE(areAlmostEqual(layout->get("Button2")->getSize(), sf::Vector2f({ 247.5,400 })));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			auto button4 = ire::core::widgets::Button::create();
			layout->add(std::move(button4), "Button4");
			auto button5 = ire::core::widgets::Button::create();
			layout->add(std::move(button5), "Button5");

			REQUIRE(areAlmostEqual(layout->get("Button3")->getPosition(), sf::Vector2f({ 252, 50 })));
			REQUIRE(areAlmostEqual(layout->get("Button3")->getSize(), sf::Vector2f({ 96, 400 })));

			REQUIRE(areAlmostEqual(layout->get("Button4")->getPosition(), sf::Vector2f({ 353, 50 })));
			REQUIRE(areAlmostEqual(layout->get("Button4")->getSize(), sf::Vector2f({ 96, 400 })));

			REQUIRE(areAlmostEqual(layout->get("Button5")->getPosition(), sf::Vector2f({ 454, 50 })));
			REQUIRE(areAlmostEqual(layout->get("Button5")->getSize(), sf::Vector2f({ 96, 400 })));
		}
		SECTION("Without Spacing With Margins")
		{
			layout->setMargins({ 5, 5, 4, 4 });
			layout->setSpaces(0);
			auto button1 = ire::core::widgets::Button::create();
			layout->add(std::move(button1), "Button1");

			REQUIRE(areAlmostEqual(layout->get("Button1")->getPosition(), sf::Vector2f({ 55, 54 })));
			REQUIRE(areAlmostEqual(layout->get("Button1")->getSize(), sf::Vector2f({ 490, 392 })));

			auto button2 = ire::core::widgets::Button::create();
			layout->add(std::move(button2), "Button2");

			REQUIRE(areAlmostEqual(layout->get("Button2")->getPosition(), sf::Vector2f({ 300, 54 })));
			REQUIRE(areAlmostEqual(layout->get("Button2")->getSize(), sf::Vector2f({ 245, 392 })));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			auto button4 = ire::core::widgets::Button::create();
			layout->add(std::move(button4), "Button4");
			auto button5 = ire::core::widgets::Button::create();
			layout->add(std::move(button5), "Button5");

			REQUIRE(areAlmostEqual(layout->get("Button3")->getPosition(), sf::Vector2f({ 251, 54 })));
			REQUIRE(areAlmostEqual(layout->get("Button3")->getSize(), sf::Vector2f({ 98, 392 })));

			REQUIRE(areAlmostEqual(layout->get("Button4")->getPosition(), sf::Vector2f({ 349, 54 })));
			REQUIRE(areAlmostEqual(layout->get("Button4")->getSize(), sf::Vector2f({ 98, 392 })));

			REQUIRE(areAlmostEqual(layout->get("Button5")->getPosition(), sf::Vector2f({ 447, 54 })));
			REQUIRE(areAlmostEqual(layout->get("Button5")->getSize(), sf::Vector2f({ 98, 392 })));

		}
		SECTION("With Spacing With Margins")
		{
			layout->setMargins({ 4, 4, 4, 4 });
			layout->setSpaces(3);
			auto button1 = ire::core::widgets::Button::create();
			layout->add(std::move(button1), "Button1");

			REQUIRE(areAlmostEqual(layout->get("Button1")->getPosition(), sf::Vector2f({ 54, 54 })));
			REQUIRE(areAlmostEqual(layout->get("Button1")->getSize(), sf::Vector2f({ 492, 392 })));

			auto button2 = ire::core::widgets::Button::create();
			layout->add(std::move(button2), "Button2");

			REQUIRE(areAlmostEqual(layout->get("Button2")->getPosition(), sf::Vector2f({ 301.5, 54 })));
			REQUIRE(areAlmostEqual(layout->get("Button2")->getSize(), sf::Vector2f({ 244.5, 392 })));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			auto button4 = ire::core::widgets::Button::create();
			layout->add(std::move(button4), "Button4");
			auto button5 = ire::core::widgets::Button::create();
			layout->add(std::move(button5), "Button5");

			REQUIRE(areAlmostEqual(layout->get("Button3")->getPosition(), sf::Vector2f({ 252, 54 })));
			REQUIRE(areAlmostEqual(layout->get("Button3")->getSize(), sf::Vector2f({ 96, 392 })));

			REQUIRE(areAlmostEqual(layout->get("Button4")->getPosition(), sf::Vector2f({ 351, 54 })));
			REQUIRE(areAlmostEqual(layout->get("Button4")->getSize(), sf::Vector2f({ 96, 392 })));

			REQUIRE(areAlmostEqual(layout->get("Button5")->getPosition(), sf::Vector2f({ 450, 54 })));
			REQUIRE(areAlmostEqual(layout->get("Button5")->getSize(), sf::Vector2f({ 96, 392 })));
		}
	}
	SECTION("Layout Stretch")
	{
		layout->setSize({ 1000,500 });
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
			REQUIRE(areAlmostEqual(layout->get("Button1")->getSize(), sf::Vector2f({ 333 ,500 })));

			REQUIRE(areAlmostEqual(layout->get("Button2")->getPosition(), sf::Vector2f({ 383 ,50 })));
			REQUIRE(areAlmostEqual(layout->get("Button2")->getSize(), sf::Vector2f({ 667 ,500 })));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			layout->setLayoutStretch({ 1, 2, 1 });
			REQUIRE(areAlmostEqual(layout->get("Button3")->getPosition(), sf::Vector2f({ 800 ,50 })));
			REQUIRE(areAlmostEqual(layout->get("Button3")->getSize(), sf::Vector2f({ 250 ,500 })));
		}
		SECTION("With margins and without spacing")
		{
			layout->setSpaces(0);
			layout->setMargins({ 6, 6, 5, 5 });

			auto button1 = ire::core::widgets::Button::create();
			layout->add(std::move(button1), "Button1");
			auto button2 = ire::core::widgets::Button::create();
			layout->add(std::move(button2), "Button2");

			layout->setLayoutStretch({ 1,2 });
			REQUIRE(areAlmostEqual(layout->get("Button1")->getPosition(), sf::Vector2f({ 56 , 55 })));
			REQUIRE(areAlmostEqual(layout->get("Button1")->getSize(), sf::Vector2f({ 329 ,489 })));

			REQUIRE(areAlmostEqual(layout->get("Button2")->getPosition(), sf::Vector2f({ 386 ,55 })));
			REQUIRE(areAlmostEqual(layout->get("Button2")->getSize(), sf::Vector2f({ 659 ,490 })));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			layout->setLayoutStretch({ 1, 2, 1 });
			REQUIRE(areAlmostEqual(layout->get("Button3")->getPosition(), sf::Vector2f({ 798 ,55 })));
			REQUIRE(areAlmostEqual(layout->get("Button3")->getSize(), sf::Vector2f({ 246 ,490 })));
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
			REQUIRE(areAlmostEqual(layout->get("Button1")->getSize(), sf::Vector2f({ 332 ,500 })));
			REQUIRE(areAlmostEqual(layout->get("Button2")->getPosition(), sf::Vector2f({ 387 ,50 })));
			REQUIRE(areAlmostEqual(layout->get("Button2")->getSize(), sf::Vector2f({ 663 ,500 })));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			layout->setLayoutStretch({ 1, 2, 1 });
			REQUIRE(areAlmostEqual(layout->get("Button3")->getPosition(), sf::Vector2f({ 803 ,50 })));
			REQUIRE(areAlmostEqual(layout->get("Button3")->getSize(), sf::Vector2f({ 247 ,500 })));
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
			REQUIRE(areAlmostEqual(layout->get("Button1")->getSize(), sf::Vector2f({ 328 ,490 })));

			REQUIRE(areAlmostEqual(layout->get("Button2")->getPosition(), sf::Vector2f({ 388 ,55 })));
			REQUIRE(areAlmostEqual(layout->get("Button2")->getSize(), sf::Vector2f({ 657 , 490 })));

			auto button3 = ire::core::widgets::Button::create();
			layout->add(std::move(button3), "Button3");
			layout->setLayoutStretch({ 1, 2, 1 });
			REQUIRE(areAlmostEqual(layout->get("Button3")->getPosition(), sf::Vector2f({ 800 ,55 })));
			REQUIRE(areAlmostEqual(layout->get("Button3")->getSize(), sf::Vector2f({ 245 ,490 })));
		}
	}
	SECTION("Spaces")
	{
		REQUIRE(layout->getSpaces() == 1);

		layout->setSpaces(5);
		REQUIRE(layout->getSpaces() == 5);
	}
}
