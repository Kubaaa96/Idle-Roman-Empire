#include "IntroState.h"
#include "client/Game/GameWindow.h"
#include "MenuState.h"
#include <iostream>

namespace ire::client::state
{
    IntroState::IntroState(core::state::StateMachine& machine, core::gui::SystemWindow& window, bool replace)
        : State {machine, window, replace}
    {
        m_window.setRootGroup(*drawGUI());
        std::cout << "IntroState Init\n";
    }

    void IntroState::pause()
    {
        std::cout << "IntroState Pause\n";
    }

    void IntroState::resume()
    {
        std::cout << "IntroState Resume\n";
    }

    void IntroState::draw()
    {
        m_window.draw();
    }
    core::gui::Group* IntroState::drawGUI()
    {
        auto btn1Ptr = ire::core::gui::Button::create("test");
        btn1Ptr->setSize({ 100, 100 });
        btn1Ptr->addEventListener<ire::core::gui::MouseClickEvent>(
            [=](ire::core::gui::MouseClickEvent& ev)
            {
                std::cout << "Clicked btn1Ptr button, Intro State\n";
                m_next = core::state::StateMachine::build<MenuState>(m_machine, m_window, true);
            });

        group = ire::core::gui::Group::create(static_cast<sf::Vector2f>(m_window.getRenderTarget().getSize()));
        group->add(std::move(btn1Ptr), "Test1");
        return group.release();
    }
}