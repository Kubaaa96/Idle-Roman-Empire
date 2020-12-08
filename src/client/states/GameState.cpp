#include "GameState.h"
#include "client/Game/GameWindow.h"
#include "MenuState.h"
#include <iostream>

namespace ire::client::state
{
    GameState::GameState(core::state::StateMachine& stateMachine, core::gui::SystemWindow& window, bool replace)
        : State{ stateMachine, window, replace}
    {
        m_window.setRootGroup(*initializeGUI());
        std::cout << "GameState Init\n";
    }

    void GameState::draw()
    {    
        std::cout << m_group->get("progressBarExamplePanel")->getType().getName() << "\n";

        m_window.draw();
    }
    core::gui::Group* GameState::initializeGUI()
    {
        auto verticalLayout = ire::core::gui::VerticalLayout::create({ 500, 400 });
        verticalLayout->setSpaces(5);
        verticalLayout->setMargins({ 0, 0, 15, 15 });
        auto btn5Ptr = ire::core::gui::Button::create("test");
        auto btn6Ptr = ire::core::gui::Button::create("test1");
        auto label7Ptr = ire::core::gui::Label::create("test");
        auto editBox8Ptr = ire::core::gui::EditBox::create("test1");
        editBox8Ptr->setGhostTextString("Enter Text...");

        btn5Ptr->addEventListener<ire::core::gui::MouseClickEvent>(
            [=](ire::core::gui::MouseClickEvent& ev)
            {
                std::cout << "Clicked btn5Ptr button, Game State\n";
                m_next = std::make_unique<MenuState>(m_stateMachine, m_window, false);
            });

        btn6Ptr->addEventListener<ire::core::gui::MouseClickEvent>(
            [](ire::core::gui::MouseClickEvent& ev)
            {
                std::cout << "Clicked btn6Ptr button " << ev.position.x << "\n";
            });

        verticalLayout->add(std::move(btn5Ptr), "Button5");
        verticalLayout->add(std::move(btn6Ptr), "Button6");
        verticalLayout->add(std::move(label7Ptr), "Label1");
        verticalLayout->add(std::move(editBox8Ptr), "EditBox1");

        verticalLayout->setLayoutStretch({ 1, 3, 6, 2 });

        auto horizontalLayout = ire::core::gui::HorizontalLayout::create({ 500,400 });
        horizontalLayout->setSpaces(10);
        horizontalLayout->setMargins({ 10, 10, 10, 10 });
        auto editBox1Ptr = ire::core::gui::EditBox::create("test");
        editBox1Ptr->setTextString("Welcome");
        auto btn2Ptr = ire::core::gui::Button::create("test1");
        auto label3Ptr = ire::core::gui::Label::create("test");
        auto btn4Ptr = ire::core::gui::Button::create("test1");

        btn2Ptr->addEventListener<ire::core::gui::MouseClickEvent>(
            [](ire::core::gui::MouseClickEvent& ev) { std::cout << "Clicked btn2Ptr button\n"; });

        btn4Ptr->addEventListener<ire::core::gui::MouseClickEvent>(
            [](ire::core::gui::MouseClickEvent& ev) { std::cout << "Clicked btn4Ptr button\n"; });

        horizontalLayout->add(std::move(editBox1Ptr), "EditBox2");
        horizontalLayout->add(std::move(btn2Ptr), "Button2");
        horizontalLayout->add(std::move(verticalLayout), "VerticalLayout");
        horizontalLayout->add(std::move(label3Ptr), "Label2");
        horizontalLayout->add(std::move(btn4Ptr), "Button4");

        horizontalLayout->setLayoutStretch({ 3, 6, 12, 2, 1 });

        auto panel = ire::core::gui::Panel::create({ 700, 400 }, std::move(horizontalLayout), "HorizontalLayout");
        panel->setPosition({ 300, 350 });
        panel->setOpacity(200);
        panel->setOutlineColor(sf::Color::Magenta);
        panel->setOutlineThickness(7);

        auto verticalLayout2 = ire::core::gui::VerticalLayout::create({ 100, 200 });
        verticalLayout2->setSpaces(5);
        verticalLayout2->setMargins({ 5, 5, 5, 5 });

        auto btn10Ptr = ire::core::gui::Button::create("elo");
        btn10Ptr->addEventListener<ire::core::gui::MouseClickEvent>(
            [](ire::core::gui::MouseClickEvent& ev) { std::cout << "Clicked btn10Ptr button\n"; });
        verticalLayout2->add(std::move(btn10Ptr), "Button10");

        auto btn11Ptr = ire::core::gui::Button::create("elo2");
        btn11Ptr->addEventListener<ire::core::gui::MouseClickEvent>(
            [](ire::core::gui::MouseClickEvent& ev) { std::cout << "Clicked btn11Ptr button\n"; });

        verticalLayout2->add(std::move(btn11Ptr), "Button11");

        auto panel2 = ire::core::gui::Panel::create({ 100, 200 }, std::move(verticalLayout2), "VerticalLayout2");
        panel2->setPosition({ 100, 100 });
        panel2->setOutlineColor(sf::Color::Red);
        panel2->setOutlineThickness(7);


        auto editBoxExampleVerticalLayout = ire::core::gui::VerticalLayout::create({ 100, 200 });
        editBoxExampleVerticalLayout->setSpaces(5);
        editBoxExampleVerticalLayout->setMargins({ 5, 5, 5, 5 });

        auto editBoxExample1 = ire::core::gui::EditBox::create("Example 1");
        editBoxExampleVerticalLayout->add(std::move(editBoxExample1), "EditBoxExample1");

        auto editBoxExample2 = ire::core::gui::EditBox::create("12345678901234567890");
        editBoxExampleVerticalLayout->add(std::move(editBoxExample2), "EditBoxExample2");

        auto editBoxExample3 = ire::core::gui::EditBox::create("12345678901234567890");
        editBoxExample3->setMaximumCharacters(10);
        editBoxExampleVerticalLayout->add(std::move(editBoxExample3), "EditBoxExample3");

        auto editBoxExample4 = ire::core::gui::EditBox::create("Example 4");
        editBoxExampleVerticalLayout->add(std::move(editBoxExample4), "EditBoxExample4");

        auto buttonTest = ire::core::gui::Button::create("Test");
        buttonTest->addEventListener<ire::core::gui::MouseClickEvent>(
            [=](ire::core::gui::MouseClickEvent& ev)
            {
                std::cout << testString << "\n";
            }
        );
        editBoxExampleVerticalLayout->add(std::move(buttonTest), "TestButton");


        auto editBoxExamplePanel = ire::core::gui::Panel::create({ 300, 250 }, std::move(editBoxExampleVerticalLayout), "EditBoxExampleVerticalLayout");
        editBoxExamplePanel->setPosition({ 650, 50 });
        editBoxExamplePanel->setOutlineColor(sf::Color::Blue);
        editBoxExamplePanel->setOutlineThickness(3);

        auto progressBarExampleVerticalLayout = ire::core::gui::VerticalLayout::create({ 100,200 });
        progressBarExampleVerticalLayout->setSpaces(5);
        progressBarExampleVerticalLayout->setMargins({ 5, 5, 5, 5 });

        auto progressBarExample1 = ire::core::gui::ProgressBar::create();
        progressBarExampleVerticalLayout->add(std::move(progressBarExample1), "ProgressBarExample1");

        auto progressBarExample2 = ire::core::gui::ProgressBar::create();
        progressBarExampleVerticalLayout->add(std::move(progressBarExample2), "ProgressBarExample2");

        auto progressBarExample3 = ire::core::gui::ProgressBar::create();
        progressBarExampleVerticalLayout->add(std::move(progressBarExample3), "ProgressBarExample3");

        auto progressBarExamplePanel = ire::core::gui::Panel::create({ 300, 250 }, std::move(progressBarExampleVerticalLayout),"ProgressBarExampleVerticalLayout");
        progressBarExamplePanel->setPosition({ 300, 50 });
        progressBarExamplePanel->setOutlineColor(sf::Color::Green);
        progressBarExamplePanel->setOutlineThickness(3);

        m_group = ire::core::gui::Group::create(static_cast<sf::Vector2f>(m_window.getRenderTarget().getSize()));
        m_group->add(std::move(panel), "panel1");
        m_group->add(std::move(panel2), "panel2");
        m_group->add(std::move(editBoxExamplePanel), "EditBoxExamplePanel");
        m_group->add(std::move(progressBarExamplePanel), "ProgressBarExamplePanel");
        
        return m_group.release();
    }
}