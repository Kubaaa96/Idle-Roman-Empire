    
#include <memory>

    namespace ire::core::widgets
    {
        struct Margins
        {
            Margins();

            Margins(Margins&);
            Margins& operator=(const Margins&);
            friend bool operator==(const Margins& marginsA, const Margins& marginsB);
            friend bool operator<(const Margins& lhs, const Margins& rhs);

            Margins(Margins&&) noexcept;
            Margins& operator=(Margins&&) noexcept;
        
            Margins(float leftMargin, float rightMargin, float topMargin, float bottomMargin);

            void setLeftMargin(float value);
            const float getLeftMargin() const; 

            void setRightMargin(float value);
            const float getRightMargin() const;

            void setTopMargin(float value);
            const float getTopMargin() const;

            void setBottomMargin(float value);
            const float getBottomMargin() const;

        private:
            float m_LeftMargin{ 0 };
            float m_RightMargin{ 0 };
            float m_TopMargin{ 0 };
            float m_BottomMargin{ 0 };
        };

        bool operator<(const Margins& lhs, const Margins& rhs);
        bool operator==(const Margins& lhs, const Margins& rhs);
    }