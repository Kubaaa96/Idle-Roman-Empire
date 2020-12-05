#include "RawEventHandler.h"

namespace ire::core::gui {

	void RawEventHandler::onEvent(EventRoot& sender, MouseButtonDownEvent& ev)
	{
		emitEventIfNotHandled<MouseButtonDownEvent>(ev);
	}

	void RawEventHandler::onEvent(EventRoot& sender, MouseButtonUpEvent& ev)
	{
		emitEventIfNotHandled<MouseButtonUpEvent>(ev);
	}

	void RawEventHandler::onEvent(EventRoot& sender, MouseMovedEvent& ev)
	{
		emitEventIfNotHandled<MouseMovedEvent>(ev);
	}
	void RawEventHandler::onEvent(EventRoot& sender, TextEnteredEvent& ev)
	{
		emitEventIfNotHandled<TextEnteredEvent>(ev);
	}
	void RawEventHandler::onEvent(EventRoot& sender, KeyDownEvent& ev)
	{
		emitEventIfNotHandled<KeyDownEvent>(ev);
	}
	void RawEventHandler::onEvent(EventRoot& sender, KeyUpEvent& ev)
	{
		emitEventIfNotHandled<KeyUpEvent>(ev);
	}
}
