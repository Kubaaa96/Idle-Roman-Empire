#ifndef WIDGETTYPE_H
#define WIDGETTYPE_H

#include <string>
#include <atomic>

struct WidgetType
{
	const uint64_t getIndex() const;
	const std::string_view getName() const;

	template <typename T>
	static WidgetType create(std::string_view name)
	{
		return { makeNextId(), name };
	}

private:
	uint64_t m_index;
	std::string_view m_name;

	WidgetType(uint64_t index, std::string_view name) : m_index(index), m_name(name) {};

	friend bool operator<(const WidgetType& lhs, const WidgetType& rhs);
	friend bool operator==(const WidgetType& lhs, const WidgetType& rhs);

	// The counter is meant to works as an "RTTI"-like type_index.
	// Therefore it has to be unique for each widget type.
	// That's why we make non-templated method to contain the counter
	// as a static variable.
	[[nodiscard]] static uint64_t makeNextId()
	{
		static std::atomic<uint64_t> nextId{ 0 };
		return nextId.fetch_add(1);
	}
};

inline bool operator<(const WidgetType& lhs, const WidgetType& rhs)
{
	return lhs.m_index < rhs.m_index;
}

inline bool operator==(const WidgetType& lhs, const WidgetType& rhs)
{
	return lhs.m_index == rhs.m_index;
}


#endif // !WIDGETTYPE_H
