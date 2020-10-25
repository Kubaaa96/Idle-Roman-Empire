#ifndef WIDGETTYPE_H
#define WIDGETTYPE_H

#include <cstdint>
#include <string>
#include <atomic>

struct WidgetType
{
	uint64_t index;
	std::string_view name;

	template <typename T>
	static WidgetType create(std::string_view name)
	{
		static std::atomic<uint64_t> nextId{ 0 };
		return { nextId.fetch_add(1), name };
	}

};

inline bool operator<(const WidgetType& lhs, const WidgetType& rhs)
{
	return lhs.index < rhs.index;
}

inline bool operator==(const WidgetType& lhs, const WidgetType& rhs)
{
	return lhs.index == rhs.index;
}


#endif // !WIDGETTYPE_H
