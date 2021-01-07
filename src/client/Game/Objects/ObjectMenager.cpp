#include "ObjectMenager.h"

namespace ire::client::objects
{
    const ObjectMenager::States ObjectMenager::getState() const
    {
        return m_state;
    }
}