#include <catch2/catch.hpp>

#include "core/gui/widgets/MessageBox.h"

#include "TestsUtils.h"

TEST_CASE("[MessageBox]")
{
    auto messageBox = ire::core::gui::MessageBox::create("Test");

    SECTION("WidgetType")
    {
        REQUIRE(messageBox->getType().getName() == "MessageBox");
    }
    SECTION("SetTitle")
    {
        REQUIRE(messageBox->getTitle() == "Test");
        messageBox->setTitle("SuperTest");
        REQUIRE(messageBox->getTitle() == "SuperTest");
    }
    SECTION("SetSize")
    {
        REQUIRE(messageBox->getWindowWidth() == 600);
        messageBox->setWindowWidth(500);
        REQUIRE(messageBox->getWindowWidth() == 500);

        REQUIRE(messageBox->getWindowHeight() == 300);
        messageBox->setWindowHeight(200);
        REQUIRE(messageBox->getWindowHeight() == 200);

        messageBox->setWindowSize( 700, 400 );
        REQUIRE(messageBox->getWindowWidth() == 700);
        REQUIRE(messageBox->getWindowHeight() == 400);

        messageBox->setWindowSize({ 800, 500 });
        REQUIRE(messageBox->getWindowWidth() == 800);
        REQUIRE(messageBox->getWindowHeight() == 500);
    }
}