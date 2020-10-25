#ifndef WIDGETTYPE_H
#define WIDGETTYPE_H

#include <string>
#include <atomic>

struct WidgetType
{
	WidgetType(uint64_t index, std::string_view name) : m_index(index), m_name(name) {};

	template <typename T>
	static WidgetType create(std::string_view name)
	{
		static std::atomic<uint64_t> nextId{ 0 };
		return { nextId.fetch_add(1), name };
	}

private:
	uint64_t m_index;
	std::string_view m_name;

	friend bool operator<(const WidgetType& lhs, const WidgetType& rhs);
	friend bool operator==(const WidgetType& lhs, const WidgetType& rhs);
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
