#include <catch2/catch.hpp>
#include "core/gui/widgets/ProgressBar.h"
#include "TestsUtils.h"

TEST_CASE("[ProgressBar]")
{
    auto progressBar = ire::core::gui::ProgressBar::create();

    SECTION("WidgetType")
    {
        REQUIRE(progressBar->getType().getName() == "ProgressBar");
    }
    SECTION("Minimum")
    {
        REQUIRE(progressBar->getMinimum() == 0);
        progressBar->setMinimum(30);
        REQUIRE(progressBar->getMinimum() == 30);
        REQUIRE(progressBar->isMinimumVisible() == false);
        progressBar->setMinimumVisibility(true);
        REQUIRE(progressBar->isMinimumVisible() == true);
        
    }
    SECTION("Maximum")
    {
        REQUIRE(progressBar->getMaximum() == 100);
        progressBar->setMaximum(300);
        REQUIRE(progressBar->getMaximum() == 300);
        REQUIRE(progressBar->isMaximumVisible() == false);
        progressBar->setMaximumVisibility(true);
        REQUIRE(progressBar->isMaximumVisible() == true);
    }
    SECTION("Value")
    {
        REQUIRE(progressBar->getValue() == 50);
        progressBar->setValue(100);
        REQUIRE(progressBar->getValue() == 100);
        REQUIRE(progressBar->isValueVisible() == false);
        progressBar->setValueVisibility(true);
        REQUIRE(progressBar->isValueVisible() == true);
    }
    SECTION("Percent")
    {

    }
    SECTION("MainString")
    {

    }
    SECTION("CharacterSize")
    {

    }
    SECTION("FillColor")
    {
        SECTION("Text")
        {

        }
        SECTION("Bar")
        {

        }
        SECTION("Background")
        {

        }
    }
    SECTION("FillDirection")
    {

    }
}