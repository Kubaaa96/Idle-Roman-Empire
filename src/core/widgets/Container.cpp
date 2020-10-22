#include "Container.h"

namespace ire::core::widgets
{
	Container::Container()
	{
		
	}

	Container::~Container()
	{
	}

	Container::Container(Container&& other) noexcept
		: Widget {std::move(other)}
		, m_widgets { std::move(other.m_widgets)}
	{
	}

	Container& Container::operator=(Container&& other) noexcept
	{
		if (this != &other)
		{
			Widget::operator=(std::move(other));
			m_widgets = std::move(other.m_widgets);
		}
		return *this;
	}

	void widgets::Container::setSize(const sf::Vector2f& size)
	{
	}

	const std::vector<std::unique_ptr<Widget>>& Container::getWidgets() const
	{
		return m_widgets;
	}

	void Container::add(const std::unique_ptr<Widget>& widgetPtr, const std::string& widgetName)
	{
	}

	bool Container::remove(const std::unique_ptr<Widget>& widgetPtr)
	{
		return false;
	}

	void Container::removeAllWidgets()
	{
	}

	std::unique_ptr<Widget> Container::getWidgetAtPosition(sf::Vector2f pos) const
	{
		return std::unique_ptr<Widget>();
	}

	void Container::draw(sf::RenderWindow& window) const
	{
	}
