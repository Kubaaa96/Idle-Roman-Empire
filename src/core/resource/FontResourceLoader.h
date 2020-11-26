#ifndef IRE_FONT_RESOURCE_LOADER_H
#define IRE_FONT_RESOURCE_LOADER_H

#include "core/resource/ResourceLoader.h"
#include "core/resource/ResourcePath.h"
#include "SFML/Graphics/Font.hpp"

namespace ire::core::resource_loaders
{
	template<>
	struct ResourceLoader<sf::Font>
	{
		using ResourceType = sf::Font;
		using ResourceStorageType = sf::Font;

		static inline ResourceStorageType load(const ResourcePath& path)
		{
			sf::Font font;
			if (!font.loadFromFile(path.string()))
			{
				throw std::runtime_error("Font not finded\n");
			}
			return font;
		}
	};
}

#endif // !IRE_FONT_RESOURCE_LOADER_H