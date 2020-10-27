#ifndef MARGINS_H
#define MARGINS_H


#include <memory>

    namespace ire::core::widgets
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

            float m_Left{ 0 };
            float m_Right{ 0 };
            float m_Top{ 0 };
            float m_Bottom{ 0 };
        };

        bool operator<(const Margins& lhs, const Margins& rhs);
        bool operator==(const Margins& lhs, const Margins& rhs);
    }
#endif // !MARGINS_H
