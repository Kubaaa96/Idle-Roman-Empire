#pragma once

#include "core/resource/ResourcePath.h"
#include "core/resource/ResourceLoader.h"

#include <SFML/Graphics/Texture.hpp>

#include <filesystem>
#include <map>
#include <memory>

namespace ire::core::gfx
{

	struct TextureView
	{
		TextureView() = default;
		TextureView(const sf::Texture& texture, const sf::FloatRect& bounds);

		[[nodiscard]] const sf::Texture& getTexture() const;
		[[nodiscard]] const sf::FloatRect& getBounds() const;

	private:
		const sf::Texture* m_texture;
		sf::FloatRect m_bounds;
	};

    struct TextureAtlas
    {
		static constexpr int padding = 1;

		TextureAtlas(std::filesystem::path dir);

		[[nodiscard]] const TextureView& getTextureView(const ResourcePath& path) const;

	private:
		std::filesystem::path m_directory;
		std::unique_ptr<sf::Texture> m_texture;
		std::map<std::string, TextureView> m_textureViews;
    };

}

namespace ire::core::resource_loaders
{
	template<>
	struct ResourceLoader<gfx::TextureAtlas>
	{
		using ResourceType = gfx::TextureAtlas;
		using ResourceStorageType = std::unique_ptr<gfx::TextureAtlas>;

		static inline ResourceStorageType load(const ResourcePath& path)
		{
			return std::make_unique<gfx::TextureAtlas>(path);
		}

		static inline const ResourceType& unpack(const ResourceStorageType& packed)
		{
			return *packed;
		}
	};
}
