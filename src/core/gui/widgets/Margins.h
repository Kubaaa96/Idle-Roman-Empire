#ifndef MARGINS_H
#define MARGINS_H


#include <memory>

namespace ire::core::gui
{
    struct Margins
    {
        Margins();

        Margins(const Margins&) = default;
        Margins& operator=(const Margins&) = default;
        friend bool operator==(const Margins& marginsA, const Margins& marginsB);
        friend bool operator<(const Margins& lhs, const Margins& rhs);

        Margins(Margins&&) noexcept = default;
        Margins& operator=(Margins&&) noexcept = default;
        
        Margins(float leftMargin, float rightMargin, float topMargin, float bottomMargin);

        float m_left{ 0 };
        float m_right{ 0 };
        float m_top{ 0 };
        float m_bottom{ 0 };
    };

    bool operator<(const Margins& lhs, const Margins& rhs);
    bool operator==(const Margins& lhs, const Margins& rhs);
}
#endif // !MARGINS_H
