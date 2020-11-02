#include "WidgetType.h"

const uint64_t WidgetType::getIndex() const
{
    return m_index;
}

const std::string_view WidgetType::getName() const
{
    return m_name;
}
