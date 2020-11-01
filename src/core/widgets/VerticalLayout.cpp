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
		const auto sizeOfVector = m_widgets.size();
		const auto width = m_size.x - m_margins.m_left - m_margins.m_right;
		float heightPerOneWidget{ 0 };
		float height{ 0 };
		bool isStretchValid = isLayoutStretchValid();

		float totalHeightOfSpaces = m_spaces * (sizeOfVector - 1);
		if (!isStretchValid)
		{
			heightPerOneWidget = m_size.y / sizeOfVector;
			height = heightPerOneWidget - (m_margins.m_top + m_margins.m_bottom + totalHeightOfSpaces) / sizeOfVector;
		}

		auto position = getPosition();
		float previousPosition{ 0 };
		float previousHeight{ 0 };
		// Calculate position of widget
		for (std::size_t i = 0; i < sizeOfVector; ++i)
		{
			float positionOfNextWidgetY{ 0 };

			if (isStretchValid)
			{
				float proportion = m_layoutStretch[i] / m_sumOfLayoutStretches;
				heightPerOneWidget = proportion * m_size.y;
				height = heightPerOneWidget - ((m_margins.m_top + m_margins.m_bottom + totalHeightOfSpaces) / sizeOfVector);
				if (i == 0)
				{
					positionOfNextWidgetY = m_margins.m_top;
					previousPosition = positionOfNextWidgetY;
				}
				else 
				{
					positionOfNextWidgetY = previousPosition + previousHeight + m_spaces;
					previousPosition = positionOfNextWidgetY;
				}
				previousHeight = height;
			}
			else
			{
				positionOfNextWidgetY = m_margins.m_top + (height * i) + (m_spaces * i);
			}
			const auto positionOfNextWidgetX = m_margins.m_right;
			m_widgets[i].get()->setOrigin(position);
			m_widgets[i].get()->setLocalPosition(sf::Vector2f{ positionOfNextWidgetX, positionOfNextWidgetY });
			m_widgets[i]->setSize({ width, height });

		}
	}
}