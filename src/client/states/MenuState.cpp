#include "MenuState.h"
#include "client/Game/GameWindow.h"
#include "GameState.h"
#include <iostream>
namespace ire::client::state
{
	MenuState::MenuState(core::state::StateMachine& stateMachine, core::gui::SystemWindow& window, bool replace)
		: State { stateMachine, window, replace}
	{
		initializeGUI();
		m_window.setRootGroup(*m_group.get());
	}


	void MenuState::initializeGUI()
	{
		auto buttonStartNewGame = ire::core::gui::Button::create("New Game");
		buttonStartNewGame->addEventListener<ire::core::gui::MouseClickEvent>(
			[=](ire::core::gui::MouseClickEvent& ev)
			{
				std::cout << "Clicked btn1Ptr button , Menu State\n";
				m_next = std::make_unique<GameState>(m_stateMachine, m_window, true);
			});

		auto buttonOptions = ire::core::gui::Button::create("Options");
		buttonOptions->addEventListener<ire::core::gui::MouseClickEvent>(
			[=](ire::core::gui::MouseClickEvent& ev)
			{
				std::cout << "Open Option State\n";
			});

		auto buttonExit = ire::core::gui::Button::create("Exit");
		buttonExit->addEventListener<ire::core::gui::MouseClickEvent>(
			[=](ire::core::gui::MouseClickEvent& ev)
			{
				std::cout << "Quit...\n";
				m_window.close();
			});

		const auto currentSizeOfViewPort = static_cast<sf::Vector2f>(m_window.getRenderTarget().getSize());

		auto vLayoutMain = ire::core::gui::VerticalLayout::create(currentSizeOfViewPort);
		vLayoutMain->add(std::move(buttonStartNewGame), "buttonStartNewGame");
		vLayoutMain->add(std::move(buttonOptions), "buttonOptions");
		vLayoutMain->add(std::move(buttonExit), "buttonExit");

		vLayoutMain->setMargins({ 50, 50, 50, 50 });
		vLayoutMain->setSpaces(20);

		m_group = ire::core::gui::Group::create(currentSizeOfViewPort);
		m_group->add(std::move(vLayoutMain), "layoutMain");
	}
}