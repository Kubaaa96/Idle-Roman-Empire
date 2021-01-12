#ifndef IRE_OBJECT_H
#define IRE_OBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>

namespace ire::client::objects
{
    struct Object
    {
        using ObjectId = std::uint64_t;

        void setName(std::string& name);
        const std::string getName() const;

        void setPosition(sf::Vector2i pos);
        const sf::Vector2i getPosition() const;


    protected:

        ObjectId m_id;
        // Faction
        // Ownder
        // Family
        // FamilyColor
        // Guild
        std::string m_name;
        // Type
        // Age
        // Health
        sf::Vector2i m_position;
    };
}

#endif //!IRE_OBJECT_H