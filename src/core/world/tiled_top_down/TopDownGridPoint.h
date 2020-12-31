#pragma once

namespace ire::core::world
{

    struct TopDownGridPoint
    {
        explicit TopDownGridPoint(float elevation = 0.0f) :
            m_elevation(elevation)
        {
        }

        [[nodiscard]] float getElevation() const
        {
            return m_elevation;
        }

    private:
        float m_elevation;
    };

}
