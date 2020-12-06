#include "ProgressBar.h"

namespace ire::core::gui
{
    WidgetType const ProgressBar::m_type = WidgetType::create<ProgressBar>("ProgressBar");

    ProgressBar::ProgressBar()
	{
		m_rectangleShape.setFillColor(sf::Color::Magenta);
	}

	std::unique_ptr<ProgressBar> ProgressBar::create(const std::string& text)
	{
		auto widget = std::make_unique<ProgressBar>();

		return widget;
	}

	void ProgressBar::draw(sf::RenderTarget& target)
	{
		target.draw(m_rectangleShape);
	}

	void ProgressBar::updateWidget()
	{
		m_rectangleShape.setSize(m_size);

		m_rectangleShape.setPosition(m_position);

	}
}