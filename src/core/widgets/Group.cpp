#include "Group.h"
#include <iostream>
namespace ire::core::widgets
{

	WidgetType const Group::m_type = WidgetType::create<Group>("Group");
	Group::Group(const sf::Vector2f& size)
	{
		setSize(size);
	}

	std::unique_ptr<Group> Group::create(const sf::Vector2f& size)
	{
		return std::make_unique<Group>(size);
	}

	void Group::add(std::unique_ptr<Widget> widgetPtr, const std::string& widgetName)
	{
		Container::add(std::move(widgetPtr), widgetName);
		updateWidgets();
	}

	void Group::setPosition(const sf::Vector2f& position)
	{
		Container::setPosition(position);
		updateWidgets();
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

	void Group::draw(sf::RenderTarget& target)
	{
		for (auto& widget : m_widgets)
		{
			widget->draw(target);
		}
	}

	void Group::updateWidgets()
	{
		const auto position = getPosition();
		for (auto& widget : m_widgets) 
		{
			const auto widgetPosition = widget->getPosition();
			widget->setPosition(position + widgetPosition);
		}
	}
}
