#include "Group.h"
#include <iostream>
namespace ire::core::widgets
{

	WidgetType Group::m_type = WidgetType::create<Group>("Group");
	Group::Group(const sf::Vector2f& size)
	{
		setSize(size);
	}

	std::unique_ptr<Group> Group::create(const sf::Vector2f& size)
	{
		return std::make_unique<Group>(size);
	}

	void Group::setSize(const sf::Vector2f& size)
	{
		Container::setSize(size);
	}

	sf::Vector2f Group::getInnerSize() const
	{
		return sf::Vector2f();
	}

	sf::Vector2f Group::getChildWidgetOffset() const
	{
		return sf::Vector2f();
	}

	void Group::draw(sf::RenderTarget& target) const
	{
		for (auto& widget : m_widgets)
		{
			widget->draw(target);
		}
	}

	void Group::init()
	{
		for (auto& widget : m_widgets) 
		{
			widget->setPosition(getPosition() + widget->getPosition());
		}
	}

	std::unique_ptr<Widget> Group::clone() const
	{
		return std::unique_ptr<Widget>();
	}

}
