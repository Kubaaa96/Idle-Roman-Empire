#include "Label.h"

namespace ire::core::gui
{
	WidgetType const Label::m_type = WidgetType::create<Label>("Label");


	Label::Label()
	{
		m_rectangleShape.setFillColor(sf::Color::Green);
	}

	std::unique_ptr<Label> Label::create(const std::string& text)
	{
		auto widget = std::make_unique<Label>();

		return widget;
	}

	void Label::draw(sf::RenderTarget& target)
	{
		target.draw(m_rectangleShape);
	}

	void Label::updateWidget()
	{
		//const auto size = getSize();
		m_rectangleShape.setSize(m_size);

		//const auto position = getPosition();
		m_rectangleShape.setPosition(m_position);

	}
}
