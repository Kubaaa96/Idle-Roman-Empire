#include "Panel.h"

namespace ire::core::widgets
{
	WidgetType const Panel::m_type = WidgetType::create<Panel>("Panel");
	Panel::Panel(const sf::Vector2f& size)
		: Group(size)
	{
	}
	std::unique_ptr<Panel> Panel::create(const sf::Vector2f size)
	{
		return std::unique_ptr<Panel>();
	}
	void Panel::setSize(const sf::Vector2f& size)
	{
	}
	void Panel::draw(sf::RenderTarget& target) const
	{
	}
}