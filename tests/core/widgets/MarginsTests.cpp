#include <catch2/catch.hpp>

#include "core/gui/widgets/Margins.h"

TEST_CASE("[Margins]")
{
	auto margins = std::make_unique< ire::core::gui::Margins>();

	SECTION("Values")
	{
		REQUIRE(*margins.get() == ire::core::gui::Margins({ 0, 0, 0, 0 }));

		margins->m_left = 10;
		margins->m_top = 15;
		REQUIRE(*margins.get() == ire::core::gui::Margins({ 10, 0, 15, 0 }));

		auto margins1 = std::make_unique<ire::core::gui::Margins>( 22, 15, 54, 9);
		REQUIRE(*margins1.get() == ire::core::gui::Margins({ 22, 15, 54, 9 }));

	}
}
