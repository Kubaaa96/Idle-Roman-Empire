#include "HorizontalLayout.h"
#include <iostream>

namespace ire::core::widgets
{
	WidgetType HorizontalLayout::m_type = WidgetType::create<HorizontalLayout>("Horizontal Layout");

	HorizontalLayout::HorizontalLayout(const sf::Vector2f& size)
		: BoxLayout{size}
	{
		//updateWidgets();
	}
	std::unique_ptr<HorizontalLayout> HorizontalLayout::create(const sf::Vector2f& size)
	{
		return std::make_unique<HorizontalLayout>(size);
	}
	void HorizontalLayout::updateWidgets()
	{
		// Actual Postion of layout? 
		// Get size of Layout
		// m_widgets size
		auto position = getPosition();
		auto size = getSize();
		auto sizeOfVector = m_widgets.size();
		m_spaces = 5;
		// # Calculate size of widget
		//	Margin Right
		//	Margin Bottom

		// ## Width
		// (LayoutWidth / WidgetCount) -
		// (LeftMargin + RightMargin + (Spacing * (WidgetCount - 1)) / 4)

		auto width = (size.x / sizeOfVector) - ((m_LeftMargin + m_RightMargin + (m_spaces * (sizeOfVector - 1))) / sizeOfVector);

		// ## Height 
		// LayoutHeight - TopMargin - Bottom Margin
		auto height = size.y - m_TopMargin - m_BottomMargin;

		// # Calculate position of widget
		//  Index of current setup widget
		//	Margin Top
		//	Margin Left
		// LeftMargin + (WidthOfWidget * Index) + (Spacing * Widget)
		for (std::size_t i = 0; i < sizeOfVector; ++i)
		{
			auto positionOfNextWidgetX = m_LeftMargin + (width * i) + (m_spaces * i);
			auto positionOfNextWidgetY = m_TopMargin;
			m_widgets[i].get()->setPosition(position + sf::Vector2f{positionOfNextWidgetX, positionOfNextWidgetY});
			m_widgets[i].get()->setSize(width, height);
		}


	}
}