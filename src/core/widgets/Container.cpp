#include "Container.h"

#include <algorithm>

namespace ire::core::widgets
{
	WidgetType Container::m_type = WidgetType::create<Container>("Container");

	Container::Container()
	{
		
	}
	void widgets::Container::setSize(const sf::Vector2f& size)
	{
		Widget::setSize(size);
	}

	sf::Vector2f Container::getInnerSize() const
	{
		return getSize();
	}

	const std::vector<std::unique_ptr<Widget>>& Container::getWidgets() const
	{
		return m_widgets;
	}

	void Container::add( std::unique_ptr<Widget> widgetPtr, const std::string& widgetName)
	{
		if (!m_widgets.empty())
		{
			for (std::size_t i = 0; i < m_widgets.size(); ++i)
			{
				if (compareWithWidgetNameAt(i, widgetName))
				{
					// TODO add some debug logger information later
					std::cout << "Widget with name: " << widgetName << " already exist in this container. \n";
					return;
				}
			}
		}
		widgetPtr->setParent(this);
		widgetPtr->setWidgetName(widgetName);
		m_widgets.push_back(std::move(widgetPtr));
	}

	bool Container::remove(const std::string& widgetName)
	{
		bool isRemoved = false;
		if (!m_widgets.empty())
		{
			
			m_widgets.erase(std::find_if(m_widgets.begin(), m_widgets.end(),
				[&widgetName, &isRemoved](std::unique_ptr<Widget>& ptr)->bool
				{
					bool isErase = ptr->getWidgetName() == widgetName;
					if (isErase)
						isRemoved = true;
					return isErase;
				}));	
		}
		return isRemoved;
	}

	Widget* Container::get(int index) 
	{
		return getWidgetAt(index);
	}

	const Widget* Container::get(int index) const
	{
		return getWidgetAt(index);
	}

	Widget* Container::get(const std::string name)
	{
		for (std::size_t i = 0; i < m_widgets.size(); ++i)
		{
			if (compareWithWidgetNameAt(i, name))
			{			
				return getWidgetAt(static_cast<int>(i));
			}		
		}
		return nullptr;
	}

	const Widget* Container::get(const std::string name) const
	{
		for (std::size_t i = 0; i < m_widgets.size(); ++i)
		{
			if (compareWithWidgetNameAt(i, name))
			{
				return getWidgetAt(static_cast<int>(i));
			}
		}
		return nullptr;
	}

	void Container::draw(sf::RenderTarget& window) const
	{
		// Check if widget is visible after adding that

		for (const auto& widget : m_widgets)
		{
			widget->draw(window);
		}
	}
	WidgetType Container::getType() const
	{
		return m_type;
	}
	bool Container::compareWithWidgetNameAt(std::size_t index, const std::string& name)
	{
		return m_widgets[index].get()->getWidgetName() == name;
	}
	const bool Container::compareWithWidgetNameAt(std::size_t index, const std::string& name) const
	{
		return m_widgets[index].get()->getWidgetName() == name;
	}
	Widget* Container::getWidgetAt(int i)
	{
		return m_widgets.at(i).get();
	}
	const Widget* Container::getWidgetAt(int i) const
	{
		return m_widgets.at(i).get();
	}
}