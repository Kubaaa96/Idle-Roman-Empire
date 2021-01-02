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
        auto verticalLayout2 = ire::core::gui::VerticalLayout::create({ 100, 200 });
        verticalLayout2->setSpaces(5);
        verticalLayout2->setMargins({ 5, 5, 5, 5 });


        auto progressBarTestingMainHLayout = ire::core::gui::HorizontalLayout::create({ 0, 0 });
        progressBarTestingMainHLayout->setSpaces(15);
        progressBarTestingMainHLayout->setMargins({ 5, 5, 5, 5 });

        auto progressBarTestingVLayout1 = ire::core::gui::VerticalLayout::create({ 0, 0 });
        progressBarTestingVLayout1->setSpaces(15);
        progressBarTestingVLayout1->setMargins({ 0, 0, 5, 5 });

        auto progressBarTestingLTR1 = ire::core::gui::ProgressBar::create();
        auto& progressBarTestingLTR1Ref = *progressBarTestingLTR1;
        progressBarTestingVLayout1->add(std::move(progressBarTestingLTR1), "ProgressBarTestingLTR1");
        
        auto progressBarTestingRTL1 = ire::core::gui::ProgressBar::create();

        auto& progressBarTestingRTL1Ref = *progressBarTestingRTL1;
        progressBarTestingRTL1->setFillDirection(ire::core::gui::ProgressBar::FillDirection::RightToLeft);
        progressBarTestingVLayout1->add(std::move(progressBarTestingRTL1), "ProgressBarTestingRTL1");

        auto progressbarTestingVProgressBarHLayout1 = ire::core::gui::HorizontalLayout::create({ 0,0 });
        progressbarTestingVProgressBarHLayout1->setSpaces(5);
        auto progressBarTestingBTT1 = ire::core::gui::ProgressBar::create();
        auto& progressBarTestingBTT1Ref = *progressBarTestingBTT1;
        progressBarTestingBTT1->setFillDirection(ire::core::gui::ProgressBar::FillDirection::BottomToTop);
        progressbarTestingVProgressBarHLayout1->add(std::move(progressBarTestingBTT1), "ProgressBarTestingBTT1");

        auto progressBarTestingTTB1 = ire::core::gui::ProgressBar::create();
        auto& progressBarTestingTTB1Ref = *progressBarTestingTTB1;
        progressBarTestingTTB1->setFillDirection(ire::core::gui::ProgressBar::FillDirection::TopToBottom);
        progressbarTestingVProgressBarHLayout1->add(std::move(progressBarTestingTTB1), "ProgressBarTestingTTB1");

        progressBarTestingVLayout1->add(std::move(progressbarTestingVProgressBarHLayout1), "ProgressBarTestingVprogressBarHLayout1");

        auto progressBarTestingBTNEditBoxHlayout1 = ire::core::gui::HorizontalLayout::create({ 0, 0 });
        progressBarTestingBTNEditBoxHlayout1->setSpaces(5);
        auto progressBarTestingEditBox1 = ire::core::gui::EditBox::create("0");
        auto& progressBarTestingEditBox1Ref = *progressBarTestingEditBox1;
        progressBarTestingEditBox1->setCharacterSize(25);
        progressBarTestingBTNEditBoxHlayout1->add(std::move(progressBarTestingEditBox1), "progressBarTestingEditBox1");

        auto progressBarTestingButton1 = ire::core::gui::Button::create("Apply");
        progressBarTestingButton1->setCharacterSize(15);
        progressBarTestingButton1->addEventListener<ire::core::gui::MouseClickEvent>(
            [&](ire::core::gui::MouseClickEvent& ev)
            {
                progressBarTestingLTR1Ref.setValue(std::stoll(progressBarTestingEditBox1Ref.getTextString()));
                progressBarTestingRTL1Ref.setValue(std::stoll(progressBarTestingEditBox1Ref.getTextString()));
                progressBarTestingBTT1Ref.setValue(std::stoll(progressBarTestingEditBox1Ref.getTextString()));
                progressBarTestingTTB1Ref.setValue(std::stoll(progressBarTestingEditBox1Ref.getTextString()));
            }
        );
        progressBarTestingBTNEditBoxHlayout1->add(std::move(progressBarTestingButton1), "progressBarTestingButton1");

        progressBarTestingVLayout1->add(std::move(progressBarTestingBTNEditBoxHlayout1), "ProgressBarTestingBTNEditBoxHlayout1");

        progressBarTestingMainHLayout->add(std::move(progressBarTestingVLayout1), "ProgressBartTestingVLayout1");


        auto progressBarTestingVLayout2 = ire::core::gui::VerticalLayout::create({ 0, 0 });
        progressBarTestingVLayout2->setSpaces(15);
        progressBarTestingVLayout2->setMargins({ 0, 0, 5, 5 });

        auto progressBarTestingLTR2 = ire::core::gui::ProgressBar::create();
        auto& progressBarTestingLTR2Ref = *progressBarTestingLTR2;
        progressBarTestingLTR2->setValueVisibility(true);
        progressBarTestingLTR2->setPercentVisibility(false);
        progressBarTestingVLayout2->add(std::move(progressBarTestingLTR2), "ProgressBarTestingLTR2");

        auto progressBarTestingRTL2= ire::core::gui::ProgressBar::create();
        auto& progressBarTestingRTL2Ref = *progressBarTestingRTL2;
        progressBarTestingRTL2->setFillDirection(ire::core::gui::ProgressBar::FillDirection::RightToLeft);
        progressBarTestingRTL2->setValueVisibility(true);
        progressBarTestingRTL2->setPercentVisibility(false);
        progressBarTestingVLayout2->add(std::move(progressBarTestingRTL2), "ProgressBarTestingRTL2");

        auto progressbarTestingVProgressBarHLayout2 = ire::core::gui::HorizontalLayout::create({ 0,0 });

        auto progressBarTestingBTT2 = ire::core::gui::ProgressBar::create();
        auto& progressBarTestingBTT2Ref = *progressBarTestingBTT2;
        progressBarTestingBTT2->setFillDirection(ire::core::gui::ProgressBar::FillDirection::BottomToTop);
        progressBarTestingBTT2->setValueVisibility(true);
        progressBarTestingBTT2->setPercentVisibility(false);
        progressbarTestingVProgressBarHLayout2->add(std::move(progressBarTestingBTT2), "ProgressBarTestingBTT2");

        auto progressBarTestingTTB2 = ire::core::gui::ProgressBar::create();
        auto& progressBarTestingTTB2Ref = *progressBarTestingTTB2;
        progressBarTestingTTB2->setFillDirection(ire::core::gui::ProgressBar::FillDirection::TopToBottom);
        progressBarTestingTTB2->setValueVisibility(true);
        progressBarTestingTTB2->setPercentVisibility(false);
        progressbarTestingVProgressBarHLayout2->add(std::move(progressBarTestingTTB2), "ProgressBarTestingTTB2");

        progressBarTestingVLayout2->add(std::move(progressbarTestingVProgressBarHLayout2), "ProgressBarTestingVprogressBarHLayout2");

        auto progressBarTestingBTNEditBoxHlayout2 = ire::core::gui::HorizontalLayout::create({ 0, 0 });
        progressBarTestingBTNEditBoxHlayout2->setSpaces(5);
        auto progressBarTestingEditBox2 = ire::core::gui::EditBox::create("0");
        auto& progressBarTestingEditBox2Ref = *progressBarTestingEditBox2;
        progressBarTestingEditBox2->setCharacterSize(25);
        progressBarTestingBTNEditBoxHlayout2->add(std::move(progressBarTestingEditBox2), "progressBarTestingEditBox2");

        auto progressBarTestingButton2 = ire::core::gui::Button::create("Apply");
        progressBarTestingButton2->addEventListener<ire::core::gui::MouseClickEvent>(
            [&](ire::core::gui::MouseClickEvent& ev)
            {
                progressBarTestingLTR2Ref.setValue(std::stoll(progressBarTestingEditBox2Ref.getTextString()));
                progressBarTestingRTL2Ref.setValue(std::stoll(progressBarTestingEditBox2Ref.getTextString()));
                progressBarTestingBTT2Ref.setValue(std::stoll(progressBarTestingEditBox2Ref.getTextString()));
                progressBarTestingTTB2Ref.setValue(std::stoll(progressBarTestingEditBox2Ref.getTextString()));
            }
        );
        progressBarTestingButton2->setCharacterSize(15);
        progressBarTestingBTNEditBoxHlayout2->add(std::move(progressBarTestingButton2), "progressBarTestingButton2");

        progressBarTestingVLayout2->add(std::move(progressBarTestingBTNEditBoxHlayout2), "ProgressBarTestingBTNEditBoxHlayout2");

        progressBarTestingMainHLayout->add(std::move(progressBarTestingVLayout2), "ProgressBartTestingVLayout2");


        auto progressBarTestingVLayout3 = ire::core::gui::VerticalLayout::create({ 0, 0 });
        progressBarTestingVLayout3->setSpaces(15);
        progressBarTestingVLayout3->setMargins({ 0, 0, 5, 5 });

        auto progressBarTestingLTR3 = ire::core::gui::ProgressBar::create("Right");
        auto& progressBarTestingLTR3Ref = *progressBarTestingLTR3;
        progressBarTestingLTR3->setPercentVisibility(false);
        progressBarTestingLTR3->setMainVisibility(true);
        progressBarTestingVLayout3->add(std::move(progressBarTestingLTR3), "ProgressBarTestingLTR3");

        auto progressBarTestingRTL3 = ire::core::gui::ProgressBar::create("Left");
        auto& progressBarTestingRTL3Ref = *progressBarTestingRTL3;
        progressBarTestingRTL3->setFillDirection(ire::core::gui::ProgressBar::FillDirection::RightToLeft);
        progressBarTestingRTL3->setPercentVisibility(false);
        progressBarTestingRTL3->setMainVisibility(true);
        progressBarTestingVLayout3->add(std::move(progressBarTestingRTL3), "ProgressBarTestingRTL3");

        auto progressbarTestingVProgressBarHLayout3 = ire::core::gui::HorizontalLayout::create({ 0,0 });

        auto progressBarTestingBTT3 = ire::core::gui::ProgressBar::create("Up");
        auto& progressBarTestingBTT3Ref = *progressBarTestingBTT3;
        progressBarTestingBTT3->setFillDirection(ire::core::gui::ProgressBar::FillDirection::BottomToTop);
        progressBarTestingBTT3->setPercentVisibility(false);
        progressBarTestingBTT3->setMainVisibility(true);
        progressbarTestingVProgressBarHLayout3->add(std::move(progressBarTestingBTT3), "ProgressBarTestingBTT3");

        auto progressBarTestingTTB3 = ire::core::gui::ProgressBar::create("Down");
        auto& progressBarTestingTTB3Ref = *progressBarTestingTTB3;
        progressBarTestingTTB3->setFillDirection(ire::core::gui::ProgressBar::FillDirection::TopToBottom);
        progressBarTestingTTB3->setPercentVisibility(false);
        progressBarTestingTTB3->setMainVisibility(true);
        progressbarTestingVProgressBarHLayout3->add(std::move(progressBarTestingTTB3), "ProgressBarTestingTTB3");

        progressBarTestingVLayout3->add(std::move(progressbarTestingVProgressBarHLayout3), "ProgressBarTestingVprogressBarHLayout3");

        auto progressBarTestingBTNEditBoxHlayout3 = ire::core::gui::HorizontalLayout::create({ 0, 0 });
        progressBarTestingBTNEditBoxHlayout3->setSpaces(5);
        auto progressBarTestingEditBox3 = ire::core::gui::EditBox::create("0");
        auto& progressBarTestingEditBox3Ref = *progressBarTestingEditBox3;
        progressBarTestingEditBox3->setCharacterSize(25);
        progressBarTestingBTNEditBoxHlayout3->add(std::move(progressBarTestingEditBox3), "progressBarTestingEditBox3");

        auto progressBarTestingButton3 = ire::core::gui::Button::create("Apply");
        progressBarTestingButton3->addEventListener<ire::core::gui::MouseClickEvent>(
            [&](ire::core::gui::MouseClickEvent& ev)
            {
                progressBarTestingLTR3Ref.setValue(std::stoll(progressBarTestingEditBox3Ref.getTextString()));
                progressBarTestingRTL3Ref.setValue(std::stoll(progressBarTestingEditBox3Ref.getTextString()));
                progressBarTestingBTT3Ref.setValue(std::stoll(progressBarTestingEditBox3Ref.getTextString()));
                progressBarTestingTTB3Ref.setValue(std::stoll(progressBarTestingEditBox3Ref.getTextString()));
            }
        );
        progressBarTestingButton3->setCharacterSize(15);
        progressBarTestingBTNEditBoxHlayout3->add(std::move(progressBarTestingButton3), "progressBarTestingButton3");

        progressBarTestingVLayout3->add(std::move(progressBarTestingBTNEditBoxHlayout3), "ProgressBarTestingBTNEditBoxHlayout3");

        progressBarTestingMainHLayout->add(std::move(progressBarTestingVLayout3), "ProgressBartTestingVLayout3");

        auto progressBarTestingPanel = ire::core::gui::Panel::create({ 950, 200 }, std::move(progressBarTestingMainHLayout), "ProgressBarTestingMainHLayout");
        progressBarTestingPanel->setPosition({ 50, 550 });
        progressBarTestingPanel->setOutlineColor(sf::Color::Green);
        progressBarTestingPanel->setOutlineThickness(3);

        auto worldView = gui::WorldView::create(*m_world);

        auto finalLayout = ire::core::gui::VerticalLayout::create(static_cast<sf::Vector2f>(m_window.getRenderTarget().getSize()));
        finalLayout->add(std::move(worldView), "WorldView");
        finalLayout->add(std::move(progressBarTestingPanel), "ProgressBarTestingPanel");
        finalLayout->setLayoutStretch({ 4.0f, 1.0f });

        m_group = std::move(finalLayout);
    }
}