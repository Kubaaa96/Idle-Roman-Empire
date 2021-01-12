#include "GameState.h"

#include "MenuState.h"

#include "client/Game/GameWindow.h"

#include "core/world/tiled_top_down/TiledTopDownSurface.h"

namespace ire::client::state
{
    GameState::GameState(core::state::StateMachine& stateMachine, core::gui::SystemWindow& window, bool replace)
        : State{ stateMachine, window, replace },
        m_world(std::make_unique<core::world::World>(
            std::make_unique<core::world::TiledTopDownSurface>(512, 512, 
                std::make_unique<core::world::objects::ObjectManager>())))
    {
        initializeGUI();
        m_window.setRootGroup(*m_group.get());
    }

    void GameState::initializeGUI()
    {        

        auto buildingControlingVerticalLayout = ire::core::gui::VerticalLayout::create({ 0,0 });

        auto buildingApplyingButton2 = ire::core::gui::Button::create("Road");
        auto& buildingApplyingButton2Ref = *buildingApplyingButton2;

        buildingApplyingButton2->addEventListener<ire::core::gui::MouseClickEvent>(
            [&](ire::core::gui::MouseClickEvent& ev)
            {
                auto objectMenager = m_world->getMainSurface().getObjectMenager();
                auto road = std::make_unique<client::objects::Road>();
                road->setState(core::world::objects::Building::States::Planned);
                objectMenager->setSelectedBuilding(road.get());
                objectMenager->appendBuildingsToVector(std::move(road));
                objectMenager->setPlanning(true);
            }
        );

        buildingControlingVerticalLayout->add(std::move(buildingApplyingButton2), "BuildingApplyingButton2");

        auto buildingApplyingButton3 = ire::core::gui::Button::create("Warehouse");
        auto& buildingApplyingButton3Ref = *buildingApplyingButton3;

        buildingApplyingButton3->addEventListener<ire::core::gui::MouseClickEvent>(
            [&](ire::core::gui::MouseClickEvent& ev)
            {
                auto objectMenager = m_world->getMainSurface().getObjectMenager();
                auto warehouse = std::make_unique<client::objects::Warehouse>();
                warehouse->setState(core::world::objects::Building::States::Planned);
                objectMenager->setSelectedBuilding(warehouse.get());
                objectMenager->appendBuildingsToVector(std::move(warehouse));
                objectMenager->setPlanning(true);
            }
        );

        buildingControlingVerticalLayout->add(std::move(buildingApplyingButton3), "BuildingApplyingButton3");

        auto buildingEditBox = ire::core::gui::EditBox::create("Hi");

        auto buildingControlingPanel = ire::core::gui::Panel::create({ 200, 600 }, std::move(buildingControlingVerticalLayout), "BuildingControlingVerticalLayout");

        auto worldView = gui::WorldView::create(*m_world);
        auto& worldViewRef = *worldView;

        worldView->addEventListener<ire::core::gui::MouseClickEvent>(
            [&](ire::core::gui::MouseClickEvent& ev)
            {
                auto objectMenager = m_world->getMainSurface().getObjectMenager();
                if (objectMenager->isPlanning() && objectMenager->canBePlaced())
                {
                    objectMenager->getSelectedBuilding()->setState(core::world::objects::Building::States::Ordered);
                    auto& mainSurface = static_cast<ire::core::world::TiledTopDownSurface&>(m_world->getMainSurface());
                    auto pointedTilePos = mainSurface.mapClientToTilePosition(m_window.getRenderTarget());
                    objectMenager->getSelectedBuilding()->setupOrderedOverlay(*pointedTilePos);
                    objectMenager->setPlanning(false);
                }
            }
        );

        worldView->addEventListener<ire::core::gui::MouseMovedEvent>(
            [&](ire::core::gui::MouseMovedEvent& ev)
            {
                if (buildingApplyingButton3Ref.getClientBounds().contains(ev.position))
                {
                    m_window.setActiveWidget(buildingApplyingButton3Ref);
                }
                else if (buildingApplyingButton2Ref.getClientBounds().contains(ev.position))
                {
                    m_window.setActiveWidget(buildingApplyingButton2Ref);
                }    
            }
        );

        auto finalLayout = ire::core::gui::VerticalLayout::create(static_cast<sf::Vector2f>(m_window.getRenderTarget().getSize()));
        finalLayout->add(std::move(worldView), "WorldView");
        m_group = ire::core::gui::Group::create(static_cast<sf::Vector2f>(m_window.getRenderTarget().getSize()));
        m_group->add(std::move(finalLayout), "FinalLayout");
        m_group->add(std::move(buildingControlingPanel), "ControlingPanel");
    }
}