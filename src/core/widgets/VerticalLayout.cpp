#include "VerticalLayout.h"

namespace ire::core::widgets
{
	WidgetType const VerticalLayout::m_type = WidgetType::create<VerticalLayout>("VerticalLayout");

	VerticalLayout::VerticalLayout(const sf::Vector2f& size)
		: BoxLayout{ size }
	{
	}
	std::unique_ptr<VerticalLayout> VerticalLayout::create(const sf::Vector2f& size)
	{
		return std::make_unique<VerticalLayout>(size);
	}
	void VerticalLayout::updateWidgets()
	{
		// Calculate size of widget
		const auto size = getSize();
		const auto sizeOfVector = m_widgets.size();
		const auto width = size.x - m_margins.m_left - m_margins.m_right;
		const auto heightPerOneWidget = size.y / sizeOfVector;
		const auto totalHeightOfSpaces = m_spaces * (sizeOfVector - 1);
		const auto height = heightPerOneWidget - (m_margins.m_top + m_margins.m_bottom + totalHeightOfSpaces) / sizeOfVector;

		auto position = getPosition();
		// Calculate position of widget
		for (std::size_t i = 0; i < sizeOfVector; ++i)
		{
			const auto positionOfNextWidgetX = m_margins.m_right;
			const auto positionOfNextWidgetY = m_margins.m_top + (height * i) + (m_spaces * i);
			m_widgets[i].get()->setPosition(position + sf::Vector2f(positionOfNextWidgetX, positionOfNextWidgetY));
			m_widgets[i].get()->setSize(width, height);
		}
	}
}