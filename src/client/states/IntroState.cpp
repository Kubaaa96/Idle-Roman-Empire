#include "IntroState.h"
#include "client/Game/GameWindow.h"
#include "MenuState.h"
#include <iostream>

namespace ire::client::state
{
    IntroState::IntroState(core::state::StateMachine& stateMachine, core::gui::SystemWindow& window, bool replace)
        : State { stateMachine, window, replace}
    {
        m_window.setRootGroup(*initializeGUI());
        std::cout << "IntroState Init\n";
    }

    void IntroState::draw()
    {
        m_window.draw();
    }
    core::gui::Group* IntroState::initializeGUI()
    {
        auto labelIntroText = ire::core::gui::Label::create("Welcome in Idle Roman Empire");
        
        auto buttonContinue = ire::core::gui::Button::create("Continue");
        buttonContinue->addEventListener<ire::core::gui::MouseClickEvent>(
            [=](ire::core::gui::MouseClickEvent& ev)
            {
                std::cout << "Clicked btn1Ptr button, Intro State\n";
                m_next = std::make_unique<MenuState>(m_stateMachine, m_window, true);
            });

        const auto currentSizeOfViewPort = static_cast<sf::Vector2f>(m_window.getRenderTarget().getSize());

        auto vLayoutMain = ire::core::gui::VerticalLayout::create(currentSizeOfViewPort);

        vLayoutMain->add(std::move(labelIntroText), "labelIntroText");
        vLayoutMain->add(std::move(buttonContinue), "buttonContinue");

        vLayoutMain->setMargins({ 50, 50, 50, 50 });
        vLayoutMain->setSpaces( 20 );
        vLayoutMain->setLayoutStretch({ 3, 1 });

        group = ire::core::gui::Group::create(currentSizeOfViewPort);
        group->add(std::move(vLayoutMain), "layoutMain");
        return group.release();
    }
}