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

        void setHorizontalAlign(HorizontalAlignment horizontalAlignment);
        const HorizontalAlignment getHorizontalAlign() const;

        void setVerticalAlign(VerticalAlignment verticalAlignment);
        const VerticalAlignment getVerticalAlign() const;

        void setVisible(bool isVisible);
        const bool isVisible() const;

        void setFont(const std::string& pathToFont);

        void setTextPosition(sf::Vector2f positionOfWidget, sf::Vector2f sizeOfWidget);
    protected:

        ResourcePtr<sf::Font> m_font;

        HorizontalAlignment m_horizontalAlignment = HorizontalAlignment::Center;
        VerticalAlignment m_varticalAlignment = VerticalAlignment::Center;

        bool m_isVisible = false;

    };  
}

#endif // !IRE_TEXT