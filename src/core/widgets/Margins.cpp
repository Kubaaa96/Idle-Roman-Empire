#include "Margins.h"

namespace ire::core::widgets
{
	Margins::Margins()
	{
	}

	Margins::Margins(float leftMargin, float rightMargin, float topMargin, float bottomMargin)
		: m_Left(leftMargin)
		, m_Right(rightMargin)
		, m_Top(topMargin)
		, m_Bottom(bottomMargin)
	{
	}
	bool operator<(const Margins& lhs, const Margins& rhs)
	{
		return lhs.m_Left < rhs.m_Left&&
			lhs.m_Right < rhs.m_Right&&
			lhs.m_Top < rhs.m_Top&&
			lhs.m_Bottom < rhs.m_Bottom;
	}
	bool operator==(const Margins& lhs, const Margins& rhs)
	{
		return lhs.m_Left == rhs.m_Left &&
			lhs.m_Right == rhs.m_Right &&
			lhs.m_Top == rhs.m_Top &&
			lhs.m_Bottom == rhs.m_Bottom;
	}
}