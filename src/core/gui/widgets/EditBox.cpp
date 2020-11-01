#include "EditBox.h"

namespace ire::core::widgets
{
	WidgetType const EditBox::m_type = WidgetType::create<EditBox>("EditBox");

	EditBox::EditBox()
	{
		m_rectangleShape.setFillColor(sf::Color::Cyan);
	}

	std::unique_ptr<EditBox> EditBox::create(const std::string& text)
	{
		auto widget = std::make_unique<EditBox>();
		// Setting up text on Button in future
		return widget;
	}

	void EditBox::draw(sf::RenderTarget& target)
	{
		target.draw(m_rectangleShape);
	}

	void EditBox::updateWidget()
	{
		//const auto size = getSize();
		m_rectangleShape.setSize(m_size);

		//const auto position = getPosition();
		m_rectangleShape.setPosition(m_position);

	}
}