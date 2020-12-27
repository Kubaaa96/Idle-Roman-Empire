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
            Bottom,
            Top,
            Center,
        };

        Text(std::string string = "", sf::Color fillColor = sf::Color::Black, 
            sf::Color outlineColor = sf::Color::White, unsigned int characterSize = 15);

        void setHAlign(HorizontalAlignment horizontalAlignment);
        const HorizontalAlignment getHAlign() const;

        void setVAlign(VerticalAlignment verticalAlignment);
        const VerticalAlignment getVAlign() const;

        void setVisibility(bool isVisible);
        const bool getVisibility() const;

        void updateTextPosition(float xPosition, float yPosition, sf::Vector2f currentPosition, sf::Vector2f currentSize);

        bool m_isHAlign = true;
        bool m_isVAlign = true;

    protected:

        ResourcePtr<sf::Font> m_font;

        HorizontalAlignment m_horizontalAlignment = HorizontalAlignment::Center;
        VerticalAlignment m_varticalAlignment = VerticalAlignment::Center;

        bool m_isVisible = false;

    };  
}

#endif // !IRE_TEXT