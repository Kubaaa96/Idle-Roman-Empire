#include "GameState.h"

#include "MenuState.h"

#include "client/Game/GameWindow.h"

#include "core/world/tiled_top_down/TiledTopDownSurface.h"

namespace ire::client::state
{
    GameState::GameState(core::state::StateMachine& stateMachine, core::gui::SystemWindow& window, bool replace)
        : State{ stateMachine, window, replace },
        m_world(std::make_unique<core::world::World>(
            std::make_unique<core::world::TiledTopDownSurface>(512, 512))),
        m_objectMenager(std::make_unique<objects::ObjectMenager>())
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
                std::cout << "Road\n";
                auto road = std::make_unique<client::objects::Road>();
                road->setState(client::objects::Building::States::Planned);
                m_objectMenager->m_currentSelectedBuilding = road.get();
                m_objectMenager->appendBuildingsToVector(std::move(road));
                m_objectMenager->setPlanning(true);
            }
        );

        buildingControlingVerticalLayout->add(std::move(buildingApplyingButton2), "BuildingApplyingButton2");

        auto buildingApplyingButton3 = ire::core::gui::Button::create("Warehouse");
        auto& buildingApplyingButton3Ref = *buildingApplyingButton3;

        buildingApplyingButton3->addEventListener<ire::core::gui::MouseClickEvent>(
            [&](ire::core::gui::MouseClickEvent& ev)
            {
                std::cout << "Warehouse\n";
                auto warehouse = std::make_unique<client::objects::Warehouse>();
                warehouse->setState(client::objects::Building::States::Planned);
                m_objectMenager->m_currentSelectedBuilding = warehouse.get();
                m_objectMenager->appendBuildingsToVector(std::move(warehouse));
                m_objectMenager->setPlanning(true);

            }
        );

        buildingControlingVerticalLayout->add(std::move(buildingApplyingButton3), "BuildingApplyingButton3");

        auto buildingEditBox = ire::core::gui::EditBox::create("Hi");

        auto buildingControlingPanel = ire::core::gui::Panel::create({ 200, 600 }, std::move(buildingControlingVerticalLayout), "BuildingControlingVerticalLayout");

        auto worldView = gui::WorldView::create(*m_world, *m_objectMenager);
        auto& worldViewRef = *worldView;

        worldView->addEventListener<ire::core::gui::MouseClickEvent>(
            [&](ire::core::gui::MouseClickEvent& ev)
            {
                if (m_objectMenager->isPlanning())
                {
                    m_objectMenager->m_currentSelectedBuilding->setState(objects::Building::States::Ordered);
                    auto& mainSurface = static_cast<ire::core::world::TiledTopDownSurface&>(m_world->getMainSurface());
                    auto pointedTilePos = mainSurface.mapClientToTilePosition(m_window.getRenderTarget(), *worldViewRef.getMousePos());
                    m_objectMenager->m_currentSelectedBuilding->setupOrderedOverlay(*pointedTilePos);
                    m_objectMenager->setPlanning(false);
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