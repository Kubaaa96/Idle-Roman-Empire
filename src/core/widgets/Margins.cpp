#include "Margins.h"

namespace ire::core::widgets
{
	Margins::Margins()
	{
	}

	Margins::Margins(float leftMargin, float rightMargin, float topMargin, float bottomMargin)
		: m_left(leftMargin)
		, m_right(rightMargin)
		, m_top(topMargin)
		, m_bottom(bottomMargin)
	{
	}
	bool operator<(const Margins& lhs, const Margins& rhs)
	{
		return lhs.m_left < rhs.m_left&&
			lhs.m_right < rhs.m_right&&
			lhs.m_top < rhs.m_top&&
			lhs.m_bottom < rhs.m_bottom;
	}
	bool operator==(const Margins& lhs, const Margins& rhs)
	{
		return lhs.m_left == rhs.m_left &&
			lhs.m_right == rhs.m_right &&
			lhs.m_top == rhs.m_top &&
			lhs.m_bottom == rhs.m_bottom;
	}
}