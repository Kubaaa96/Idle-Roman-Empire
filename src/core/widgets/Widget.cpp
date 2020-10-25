#include "Widget.h"
#include "Container.h"

namespace ire::core::widgets
{
	Widget::~Widget()
	{
	}
	void Widget::setWidgetName(const std::string& name)
	{
		m_name = name;
	}

	std::string Widget::getWidgetName() const
	{
		return m_name;
	}

	void Widget::setPosition(const sf::Vector2f& position)
	{
		m_position = position;
	}

	void Widget::setPosition(float x, float y)
	{
		setPosition({ x, y });
	}

	sf::Vector2f Widget::getPosition() const
	{
		return m_position;
	}

	void Widget::setSize(const sf::Vector2f& size)
	{
		m_size = size;
	}

	void Widget::setSize(float x, float y)
	{
		setSize({ x ,y });
	}

	void Widget::setWidth(float width)
	{
		setSize({ std::move(width), m_size.y });
	}

	void Widget::setHeigh(float height)
	{
		setSize({ m_size.x, std::move(height) });
	}

	sf::Vector2f Widget::getSize() const
	{
		return m_size;
	}

	void Widget::setOrigin(sf::Vector2f origin)
	{
		m_origin = origin;
	}

	void Widget::setOrigin(float x, float y)
	{
		setOrigin({ x, y });
	}

	sf::Vector2f Widget::getOrigin() const
	{
		return m_origin;
	}

	void Widget::setParent(Container* parent)
	{
		if (m_parent == parent)
			return;
		m_parent = parent;
	}

	Container* Widget::getParent() const
	{
		return m_parent;

	}

	void Widget::drawRect(sf::RenderWindow& window)
	{
		sf::RectangleShape rectWidget;
		rectWidget.setPosition(m_position);
		rectWidget.setSize(m_size);
		rectWidget.setOrigin(m_origin);
		rectWidget.setFillColor(sf::Color::Red);
		window.draw(rectWidget);
	}
}