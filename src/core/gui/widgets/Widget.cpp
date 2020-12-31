#include "Widget.h"
#include "Container.h"

namespace ire::core::gui
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

	sf::Vector2f Widget::getPosition() const
	{
		return m_position;
	}

	void Widget::setLocalPosition(const sf::Vector2f& localPosition)
	{
		m_localPosition = localPosition;
		m_position = m_origin + localPosition;
	}

	sf::Vector2f Widget::getLocalPosition() const
	{
		return m_localPosition;
	}

	void Widget::setSize(const sf::Vector2f& size)
	{
		m_size = size;
	}

	void Widget::setWidth(float width)
	{
		setSize({ std::move(width), m_size.y });
	}

	void Widget::setHeight(float height)
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

	[[nodiscard]] sf::FloatRect Widget::getClientBounds() const 
	{
		return sf::FloatRect(m_position, m_size);
	}

	[[nodiscard]] sf::FloatRect Widget::getClientViewport(sf::RenderTarget& target) const
	{
		const auto size = target.getSize();
		const float left = m_position.x / size.x;
		const float top = m_position.y / size.y;
		const float width = m_size.x / size.x;
		const float height = m_size.y / size.y;
		return sf::FloatRect(left, top, width, height);
	}

	void Widget::onStoppedBeingActive()
	{
	}
}
