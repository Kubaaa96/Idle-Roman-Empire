#include "Panel.h"

#include <iostream>

namespace ire::core::widgets
{
	WidgetType const Panel::m_type = WidgetType::create<Panel>("Panel");
	Panel::Panel(const sf::Vector2f& size, std::unique_ptr<BoxLayout> mainPanelLayout, std::string& layoutName)
	{

		m_rectangleShape.setFillColor(sf::Color::White);

		m_panelLayout = std::move(mainPanelLayout);
		m_panelLayout->setWidgetName(layoutName);
		setSize(size);
	}

	std::unique_ptr<Panel> Panel::create(const sf::Vector2f size, std::unique_ptr<BoxLayout> mainPanelLayout, std::string& layoutName)
	{
		return std::make_unique<Panel>(size,  std::move(mainPanelLayout), layoutName);
	}

	void Panel::setSize(const sf::Vector2f& size)
	{
		Widget::setSize(size);
		updateLayout();
	}
	void Panel::setPosition(const sf::Vector2f& position)
	{
		Widget::setPosition(position);
		updateLayout();
	}
	void Panel::draw(sf::RenderTarget& target)
	{
		target.draw(m_rectangleShape);
		m_panelLayout->draw(target);

	}
	void Panel::setBackground(const sf::Color backgroundColor)
	{
		m_rectangleShape.setFillColor(backgroundColor);
	}
	void Panel::setOpacity(std::uint8_t alpha)
	{
		sf::Color tempColor = m_rectangleShape.getFillColor();
		m_rectangleShape.setFillColor(sf::Color(tempColor.r, tempColor.g, tempColor.b, alpha));
	}
	void Panel::setOutlineColor(const sf::Color outlineColor)
	{
		m_rectangleShape.setOutlineColor(outlineColor);
	}
	void Panel::setOutlineThickness(float thickness)
	{
		m_rectangleShape.setOutlineThickness(thickness);
	}
	void Panel::updateLayout()
	{
		const auto size = getSize();
		m_panelLayout->setSize(size);
		m_rectangleShape.setSize(size);

		const auto position = getPosition();
		m_rectangleShape.setPosition(position);
		m_panelLayout->setPosition(position);
	}
}