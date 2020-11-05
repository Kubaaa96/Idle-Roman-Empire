#include "ClickableWidget.h"
#include "WidgetType.h"

#include <iostream>

namespace ire::core::gui
{
	WidgetType const ClickableWidget::m_type = WidgetType::create<ClickableWidget>("ClickableWidget");

	ClickableWidget::ClickableWidget()
	{
	}

	void ClickableWidget::setSize(const sf::Vector2f& size)
	{
		Widget::setSize(size);
		updateWidget();
	}

	void ClickableWidget::setPosition(const sf::Vector2f& position)
	{
		Widget::setPosition(position);
		updateWidget();
	}

	void ClickableWidget::draw(sf::RenderTarget& target)
	{
	}

	void ClickableWidget::onEvent(EventRoot& sender, MouseButtonDownEvent& ev)
	{
		if (ev.button != sf::Mouse::Button::Left)
		{
			return;
		}

		m_state = State::Armed;

		ev.handled = true;
	}

	void ClickableWidget::onEvent(EventRoot& sender, MouseButtonUpEvent& ev)
	{
		if (ev.button != sf::Mouse::Button::Left)
		{
			return;
		}

		if (m_state == State::Armed && clientBounds().contains(ev.position))
		{
			onClick(ev);
		}

		m_state = State::Idle;
		ev.handled = true;

		sender.resetActiveWidget(*this);
	}

	void ClickableWidget::onEvent(EventRoot& sender, MouseMovedEvent& ev)
	{
		if (clientBounds().contains(ev.position))
		{
			m_state = (
				(m_state == State::Idle || m_state == State::Hover) 
				? State::Hover 
				: State::Armed);
		}
		else
		{
			m_state = 
				(m_state == State::Armed || m_state == State::Disarmed)
				? State::Disarmed
				: State::Idle;
		}

		ev.handled = true;

		if (m_state == State::Idle)
		{
			sender.resetActiveWidget(*this);
		}
		else
		{
			sender.setActiveWidget(*this);
		}
	}

	void ClickableWidget::onClick(MouseButtonUpEvent& ev)
	{
		MouseClickEvent clickEv{};
		clickEv.timestamp = ev.timestamp;
		clickEv.button = ev.button;
		clickEv.position = ev.position;
		emitEvent<MouseClickEvent>(clickEv);
	}
}
