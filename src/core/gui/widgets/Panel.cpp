#include "Panel.h"

namespace ire::core::gui
{
	WidgetType const Panel::m_type = WidgetType::create<Panel>("Panel");
	Panel::Panel(const sf::Vector2f& size, std::unique_ptr<BoxLayout> mainPanelLayout, const std::string& layoutName)
	{

		m_rectangleShape.setFillColor(sf::Color::White);

		m_panelLayout = std::move(mainPanelLayout);
		m_panelLayout->setWidgetName(layoutName);
		setSize(size);
	}

	std::unique_ptr<Panel> Panel::create(const sf::Vector2f size, std::unique_ptr<BoxLayout> mainPanelLayout, const std::string& layoutName)
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
	const std::unique_ptr<BoxLayout>& Panel::getLayout() const
	{
		return m_panelLayout;
	}
	void Panel::draw(sf::RenderTarget& target)
	{
		target.draw(m_rectangleShape);
		m_panelLayout->draw(target);

	}
	void Panel::setBackgroundColor(const sf::Color backgroundColor)
	{
		m_rectangleShape.setFillColor(backgroundColor);
	}
	const sf::Color Panel::getBackgroundColor() const
	{
		return m_rectangleShape.getFillColor();
	}
	void Panel::setOpacity(std::uint8_t alpha)
	{
		sf::Color tempColor = m_rectangleShape.getFillColor();
		m_rectangleShape.setFillColor(sf::Color(tempColor.r, tempColor.g, tempColor.b, alpha));
	}
	const std::uint8_t Panel::getOpacity() const
	{
		return m_rectangleShape.getFillColor().a;
	}
	void Panel::setOutlineColor(const sf::Color outlineColor)
	{
		m_rectangleShape.setOutlineColor(outlineColor);
	}
	const sf::Color Panel::getOutlineColor() const
	{
		return m_rectangleShape.getOutlineColor();
	}
	void Panel::setOutlineThickness(float thickness)
	{
		m_rectangleShape.setOutlineThickness(thickness);
	}
	const float Panel::getOutlineThickness() const
	{
		return m_rectangleShape.getOutlineThickness();
	}
	void Panel::updateLayout()
	{
		m_panelLayout->setSize(m_size);
		m_rectangleShape.setSize(m_size);

		m_rectangleShape.setPosition(m_position);
		m_panelLayout->setOrigin(m_position);
		m_panelLayout->setLocalPosition({0, 0});
	}

	void Panel::onEvent(MouseButtonDownEvent& ev)
	{
		m_panelLayout->onEvent(ev);

		Widget::onEvent(ev);
	}
}