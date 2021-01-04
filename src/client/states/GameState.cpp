#include "GameState.h"

#include "MenuState.h"

#include "client/Game/GameWindow.h"

#include "core/world/tiled_top_down/TiledTopDownSurface.h"

namespace ire::client::state
{
    GameState::GameState(core::state::StateMachine& stateMachine, core::gui::SystemWindow& window, bool replace)
        : State{ stateMachine, window, replace },
        m_world(std::make_unique<core::world::World>(
            std::make_unique<core::world::TiledTopDownSurface>(512, 512))
        )
    {
        initializeGUI();
        m_window.setRootGroup(*m_group.get());
    }

    void GameState::initializeGUI()
    {        

        auto buildingControlingVerticalLayout = ire::core::gui::VerticalLayout::create({ 0,0 });

        auto buildingApplyingButton = ire::core::gui::Button::create("Apply");
        auto& buildingApplyingButtonRef = *buildingApplyingButton;

        buildingApplyingButton->addEventListener<ire::core::gui::MouseClickEvent>(
            [](ire::core::gui::MouseClickEvent& ev)
            {
                std::cout << "Apply\n";
            }
        );

        buildingControlingVerticalLayout->add(std::move(buildingApplyingButton), "BuildingApplyingButton");

        auto buildingControlingPanel = ire::core::gui::Panel::create({ 200, 200 }, std::move(buildingControlingVerticalLayout), "BuildingControlingVerticalLayout");

        auto worldView = gui::WorldView::create(*m_world);

        worldView->addEventListener<ire::core::gui::MouseClickEvent>(
            [&](ire::core::gui::MouseClickEvent& ev)
            {

                if (buildingApplyingButtonRef.getClientBounds().contains(ev.position))
                {
                    std::cout << "Inside Button\n";
                    m_window.setActiveWidget(buildingApplyingButtonRef);
                }
            }
        );
        auto finalLayout = ire::core::gui::VerticalLayout::create(static_cast<sf::Vector2f>(m_window.getRenderTarget().getSize()));
        finalLayout->add(std::move(worldView), "WorldView");
        m_group = ire::core::gui::Group::create(static_cast<sf::Vector2f>(m_window.getRenderTarget().getSize()));
        m_group->add(std::move(finalLayout), "FinalLayout");
        m_group->add(std::move(buildingControlingPanel), "ControlingPanel");
        //m_group = std::move(finalLayout);
    }
}