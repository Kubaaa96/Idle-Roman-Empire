#ifndef IRE_TEXT
#define IRE_TEXT

#include <SFML/Graphics.hpp>

#include "core/resource/Resource.h"
#include "core/resource/FontResourceLoader.h"
#include "core/resource/ResourceManager.h"

namespace ire::core::gui
{
    struct Text : sf::Text
    {    
        enum struct HorizontalAlignment
        {
            Left,
            Right,
            Center,
        };

        enum struct VerticalAlignment
        {
            Top,
            Bottom,
            Center,
        };

        Text(sf::String& string, sf::Color fillColor = sf::Color::Black, 
            sf::Color outlineColor = sf::Color::White, unsigned int characterSize = 15);

        void setHAlign(HorizontalAlignment horizontalAlignment);
        const HorizontalAlignment getHAlign() const;

        void setVAlign(VerticalAlignment verticalAlignment);
        const VerticalAlignment getVAlign() const;

    protected:

        HorizontalAlignment m_horizontalAlignment = HorizontalAlignment::Center;
        VerticalAlignment m_varticalAlignment = VerticalAlignment::Center;

        bool m_isVisible = false;
        bool m_isHAlignAllowed = true;
        bool m_isVAlignAllowed = true;
    };  
}

#endif // !IRE_TEXT