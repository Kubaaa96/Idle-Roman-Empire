#include "Margins.h"

namespace ire::core::widgets
{
	Margins::Margins()
	{
	}
	Margins::Margins(Margins& margins)
		: m_LeftMargin(margins.m_LeftMargin)
		, m_RightMargin(margins.m_RightMargin)
		, m_TopMargin(margins.m_TopMargin)
		, m_BottomMargin(margins.m_BottomMargin)
	{
	}
	Margins& Margins::operator=(const Margins& margins)
	{
		m_LeftMargin = margins.m_LeftMargin;
		m_RightMargin = margins.m_RightMargin;
		m_TopMargin = margins.m_TopMargin;
		m_BottomMargin = margins.m_BottomMargin;
		return *this;
	}
	Margins::Margins(Margins&& margins) noexcept
		: m_LeftMargin(std::move(margins.m_LeftMargin))
		, m_RightMargin(std::move(margins.m_RightMargin))
		, m_TopMargin(std::move(margins.m_TopMargin))
		, m_BottomMargin(std::move(margins.m_BottomMargin))
	{
	}
	Margins& Margins::operator=(Margins&& margins) noexcept
	{
		m_LeftMargin = std::move(margins.m_LeftMargin);
		m_RightMargin = std::move(margins.m_RightMargin);
		m_TopMargin = std::move(margins.m_TopMargin);
		m_BottomMargin = std::move(margins.m_BottomMargin);
		return *this;
	}
	Margins::Margins(float leftMargin, float rightMargin, float topMargin, float bottomMargin)
		: m_LeftMargin(leftMargin)
		, m_RightMargin(rightMargin)
		, m_TopMargin(topMargin)
		, m_BottomMargin(bottomMargin)
	{
	}
	void Margins::setLeftMargin(float value)
	{
		m_LeftMargin = value;
	}
	const float Margins::getLeftMargin() const
	{
		return m_LeftMargin;
	}
	void Margins::setRightMargin(float value)
	{
		m_RightMargin = value;
	}
	const float Margins::getRightMargin() const
	{
		return m_RightMargin;
	}
	void Margins::setTopMargin(float value)
	{
		m_TopMargin = value;
	}
	const float Margins::getTopMargin() const
	{
		return m_TopMargin;
	}
	void Margins::setBottomMargin(float value)
	{
		m_BottomMargin = value;
	}
	const float Margins::getBottomMargin() const
	{
		return m_BottomMargin;
	}
	bool operator<(const Margins& lhs, const Margins& rhs)
	{
		return lhs.m_LeftMargin < rhs.m_LeftMargin&&
			lhs.m_RightMargin < rhs.m_RightMargin&&
			lhs.m_TopMargin < rhs.m_TopMargin&&
			lhs.m_BottomMargin < rhs.m_BottomMargin;
	}
	bool operator==(const Margins& lhs, const Margins& rhs)
	{
		return lhs.m_LeftMargin == rhs.m_LeftMargin&&
			lhs.m_RightMargin == rhs.m_RightMargin&&
			lhs.m_TopMargin == rhs.m_TopMargin&&
			lhs.m_BottomMargin == rhs.m_BottomMargin;
	}
}