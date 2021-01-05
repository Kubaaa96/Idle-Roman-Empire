#ifndef IRE_OBJECT_H
#define IRE_OBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>

namespace ire::client::objects
{
    struct Object
    {
        void setName(std::string& name);
        const std::string getName() const;

        void setPosition(sf::Vector2i pos);
        const sf::Vector2i getPosition() const;

    protected:

        std::uint64_t m_Id;
        // Faction
        // Ownder
        // Family
        // FamilyColor
        // Guild
        std::string m_name;
        // Type
        // Age
        // Health
        sf::Vector2i m_currentPosition;
    };
}

#endif //!IRE_OBJECT_H