#include "RawEventHandler.h"

namespace ire::core::gui {

	void RawEventHandler::onEvent(EventRoot& sender, MouseButtonDownEvent& ev)
	{
		emitEventIfNotHandled<MouseButtonDownEvent>(ev);
	}

}
