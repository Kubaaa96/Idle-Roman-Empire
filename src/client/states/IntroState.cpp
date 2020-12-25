#include "IntroState.h"
#include "client/Game/GameWindow.h"
#include "MenuState.h"

#include "core/world/tiled_top_down/TiledTopDownSurface.h"
#include "core/world/World.h"

namespace ire::client::state
{
    struct WorldView : ire::core::gui::ClickableWidget
    {
        WorldView() :
            m_world(std::make_unique<ire::core::world::TiledTopDownSurface>(24, 24))
        {
        }

        static std::unique_ptr<WorldView> create()
        {
            auto widget = std::make_unique<WorldView>();
            return widget;
        }

        void draw(sf::RenderTarget& target)
        {
            sf::RenderStates states = sf::RenderStates::Default;
            sf::View view = target.getView();
            view.setViewport(sf::FloatRect(0.1, 0.1, 0.8, 0.8));
            target.setView(view);
            sf::RectangleShape s;
            s.setFillColor(sf::Color::White);
            s.setSize(sf::Vector2f(1000.0f, 1000.0f));
            target.draw(s);
            m_world.getMainSurface().draw(target, states);
        }

        void updateWidget() override {}

        static const WidgetType m_type;
        const WidgetType getType() const override
        {
            return m_type;
        }
    private:
        ire::core::world::World m_world;
    };

    const WidgetType WorldView::m_type = WidgetType::create<WorldView>("WorldView");

    IntroState::IntroState(core::state::StateMachine& stateMachine, core::gui::SystemWindow& window, bool replace)
        : State { stateMachine, window, replace}
    {
        initializeGUI();
        m_window.setRootGroup(*m_group.get());
    }

    void IntroState::initializeGUI()
    {
        auto labelIntroText = ire::core::gui::Label::create("Idle Roman Empire\n Next generation\n of Idle Gaming");
        labelIntroText->setTextLineSpacing(2);
        labelIntroText->setCharacterSize(65);
        
        auto buttonContinue = ire::core::gui::Button::create("Let's Go");
        buttonContinue->setCharacterSize(40);
        buttonContinue->addEventListener<ire::core::gui::MouseClickEvent>(
            [=](ire::core::gui::MouseClickEvent& ev)
            {
                std::cout << "Clicked btn1Ptr button, Intro State\n";
                m_next = std::make_unique<MenuState>(m_stateMachine, m_window, true);
            });

        const auto currentSizeOfViewPort = static_cast<sf::Vector2f>(m_window.getRenderTarget().getSize());

        auto vLayoutMain = ire::core::gui::VerticalLayout::create(currentSizeOfViewPort);

        vLayoutMain->add(std::move(labelIntroText), "labelIntroText");
        //vLayoutMain->add(std::move(buttonContinue), "buttonContinue");

        //vLayoutMain->setMargins({ 50, 50, 50, 50 });
        //vLayoutMain->setSpaces( 20 );
        //vLayoutMain->setLayoutStretch({ 3, 1 });

        m_group = ire::core::gui::Group::create(currentSizeOfViewPort);
        m_group->add(std::move(vLayoutMain), "layoutMain");
    }
}
