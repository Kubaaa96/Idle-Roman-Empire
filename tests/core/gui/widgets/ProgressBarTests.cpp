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

        SECTION("CharacterSize")
        {
            REQUIRE(progressBar->getMinimumTextCharacterSize() == 15);
            progressBar->setMinimumTextCharacterSize(35);
            REQUIRE(progressBar->getMinimumTextCharacterSize() == 35);
        }
        SECTION("VertocalAlignment")
        {
            REQUIRE(progressBar->getMinimumTextVerticalAlignmentString() == "Center");
            progressBar->setMinimumTextVerticalAlignment(ire::core::gui::ProgressBar::VerticalTextAlignment::Bottom);
            REQUIRE(progressBar->getMinimumTextVerticalAlignmentString() == "Bottom");
        }
        SECTION("Visibility")
        {
            REQUIRE(progressBar->isMinimumVisible() == true);
            progressBar->setMinimumVisibility(false);
            REQUIRE(progressBar->isMinimumVisible() == false);
        }
        SECTION("FillColor")
        {
            REQUIRE(progressBar->getMinimumTextFillColor() == sf::Color::Black);
            progressBar->setMinimumTextFillColor(sf::Color::Magenta);
            REQUIRE(progressBar->getMinimumTextFillColor() == sf::Color::Magenta);
        }
        
    }
    SECTION("Maximum")
    {
        REQUIRE(progressBar->getMaximum() == 100);
        progressBar->setMaximum(300);
        REQUIRE(progressBar->getMaximum() == 300);

        SECTION("CharacterSize")
        {
            REQUIRE(progressBar->getMaximumTextCharacterSize() == 15);
            progressBar->setMaximumTextCharacterSize(35);
            REQUIRE(progressBar->getMaximumTextCharacterSize() == 35);
        }
        SECTION("VerticalAlignment")
        {
            REQUIRE(progressBar->getMaximumTextVerticalAlignmentString() == "Center");
            progressBar->setMaximumTextVerticalAlignment(ire::core::gui::ProgressBar::VerticalTextAlignment::Bottom);
            REQUIRE(progressBar->getMaximumTextVerticalAlignmentString() == "Bottom");
        }
        SECTION("Visibility")
        {
            REQUIRE(progressBar->isMaximumVisible() == true);
            progressBar->setMaximumVisibility(false);
            REQUIRE(progressBar->isMaximumVisible() == false);
        }
        SECTION("FillColor")
        {
            REQUIRE(progressBar->getMaximumTextFillColor() == sf::Color::Black);
            progressBar->setMaximumTextFillColor(sf::Color::Magenta);
            REQUIRE(progressBar->getMaximumTextFillColor() == sf::Color::Magenta);
        }
    }
    SECTION("Value")
    {
        REQUIRE(progressBar->getValue() == 50);
        progressBar->setValue(100);
        REQUIRE(progressBar->getValue() == 100);

        SECTION("CharacterSize")
        {
            REQUIRE(progressBar->getValueTextCharacterSize() == 15);
            progressBar->setValueTextCharacterSize(35);
            REQUIRE(progressBar->getValueTextCharacterSize() == 35);
        }
        SECTION("VerticalAlignment")
        {
            REQUIRE(progressBar->getValueTextVerticalAlignmentString() == "Center");
            progressBar->setValueTextVerticalAlignment(ire::core::gui::ProgressBar::VerticalTextAlignment::Bottom);
            REQUIRE(progressBar->getValueTextVerticalAlignmentString() == "Bottom");
        }
        SECTION("Visibility")
        {
            REQUIRE(progressBar->isValueVisible() == false);
            progressBar->setValueVisibility(true);
            REQUIRE(progressBar->isValueVisible() == true);
        }
        SECTION("FillColor")
        {
            REQUIRE(progressBar->getValueTextFillColor() == sf::Color::Black);
            progressBar->setValueTextFillColor(sf::Color::Magenta);
            REQUIRE(progressBar->getValueTextFillColor() == sf::Color::Magenta);
        }
    }
    SECTION("Percent")
    {
        REQUIRE(progressBar->getPercent() == 0.5);
        progressBar->setValue(75);
        REQUIRE(progressBar->getPercent() == 0.75);
        SECTION("CharacterSize")
        {
            REQUIRE(progressBar->getPercentTextCharacterSize() == 15);
            progressBar->setPercentTextCharacterSize(25);
            REQUIRE(progressBar->getPercentTextCharacterSize() == 25);
        }
        SECTION("VerticalAlignment")
        {
            REQUIRE(progressBar->getPercentTextVerticalAlignmentString() == "Center");
            progressBar->setPercentTextVerticalAlignment(ire::core::gui::ProgressBar::VerticalTextAlignment::Bottom);
            REQUIRE(progressBar->getPercentTextVerticalAlignmentString() == "Bottom");
        }
        SECTION("Visibility")
        {
            REQUIRE(progressBar->isPercentVisible() == true);
            progressBar->setPercentVisibility(false);
            REQUIRE(progressBar->isPercentVisible() == false);
        }
        SECTION("FillColor")
        {
            REQUIRE(progressBar->getPercentTextFillColor() == sf::Color::Black);
            progressBar->setPercentTextFillColor(sf::Color::Magenta);
            REQUIRE(progressBar->getPercentTextFillColor() == sf::Color::Magenta);
        }
    }
    SECTION("MainString")
    {
        REQUIRE(progressBar->getMainString() == "");
        progressBar->setMainTextString("Welcome");
        REQUIRE(progressBar->getMainString() == "Welcome");
        
        SECTION("CharacterSize")
        {
            REQUIRE(progressBar->getMainTextCharacterSize() == 25);
            progressBar->setMainTextCharacterSize(15);
            REQUIRE(progressBar->getMainTextCharacterSize() == 15);
        }
        SECTION("VerticalAlignment")
        {
            REQUIRE(progressBar->getMainTextVerticalAlignmentString() == "Center");
            progressBar->setMainTextVerticalAlignment(ire::core::gui::ProgressBar::VerticalTextAlignment::Bottom);
            REQUIRE(progressBar->getMainTextVerticalAlignmentString() == "Bottom");
        }
        SECTION("Visibility")
        {
            REQUIRE(progressBar->isMainVisible() == false);
            progressBar->setMainVisibility(true);
            REQUIRE(progressBar->isMainVisible() == true);
        }
        SECTION("FillColor")
        {
            REQUIRE(progressBar->getMainTextFillColor() == sf::Color::Black);
            progressBar->setMainTextFillColor(sf::Color::Magenta);
            REQUIRE(progressBar->getMainTextFillColor() == sf::Color::Magenta);
        }
    }
    SECTION("FillColor")
    {
        SECTION("Bar")
        {
            REQUIRE(progressBar->getProgressFillColor() == sf::Color::Green);
            progressBar->setProgressFillColor(sf::Color::Magenta);
            REQUIRE(progressBar->getProgressFillColor() == sf::Color::Magenta);
        }
        SECTION("Background")
        {
            REQUIRE(progressBar->getBackgroundFillColor() == sf::Color::Blue);
            progressBar->setBackgroundFillColor(sf::Color::Red);
            REQUIRE(progressBar->getBackgroundFillColor() == sf::Color::Red);
        }
    }
    SECTION("FillDirection")
    {
        REQUIRE(progressBar->getFillDirection() == ire::core::gui::ProgressBar::FillDirection::LeftToRight);
        progressBar->setFillDirection(ire::core::gui::ProgressBar::FillDirection::RightToLeft);
        REQUIRE(progressBar->getFillDirection() == ire::core::gui::ProgressBar::FillDirection::RightToLeft);

    }
}