#include "MenuState.h"
#include "client/Game/GameWindow.h"
#include "GameState.h"
#include <iostream>
namespace ire::client::state
{
	MenuState::MenuState(core::state::StateMachine& machine, core::gui::SystemWindow& window, bool replace)
		: State {machine, window, replace}
	{
		m_window.setRootGroup(*drawGUI());
		std::cout << "MenuState Init\n";
	}

	void MenuState::pause()
	{
		std::cout << "MenuState Pause\n";
	}

	void MenuState::resume()
	{
		std::cout << "MenuState Resume\n";
	}

	void MenuState::draw()
	{
		m_window.draw();
	}

	core::gui::Group* MenuState::drawGUI()
	{
		auto btn1Ptr = ire::core::gui::Button::create("test");
		btn1Ptr->setSize({ 200, 200 });
		btn1Ptr->addEventListener<ire::core::gui::MouseClickEvent>(
			[=](ire::core::gui::MouseClickEvent& ev)
			{
				std::cout << "Clicked btn1Ptr button , Menu State\n";
				m_next = core::state::StateMachine::build<GameState>(m_machine, m_window, true);
			});
		group = ire::core::gui::Group::create(static_cast<sf::Vector2f>(m_window.getRenderTarget().getSize()));
		group->add(std::move(btn1Ptr), "Label");
		return group.release();
	}
}