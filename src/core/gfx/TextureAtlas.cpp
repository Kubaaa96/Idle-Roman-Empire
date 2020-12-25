#include "TextureAtlas.h"

#include <tuple>

namespace ire::core::gfx
{

	TextureView::TextureView(const sf::Texture& texture, const sf::FloatRect& bounds) :
		m_texture(&texture),
		m_bounds(bounds)
	{
	}

	[[nodiscard]] const sf::Texture& TextureView::getTexture() const
	{
		return *m_texture;
	}

	[[nodiscard]] const sf::FloatRect& TextureView::getBounds() const
	{
		return m_bounds;
	}

	TextureAtlas::TextureAtlas(std::filesystem::path dir) :
		m_directory(dir.lexically_normal())
	{
		// TODO: Currently loads just one texture for testing.
		//       Do proper bin packing.
		for (auto& e : std::filesystem::recursive_directory_iterator(m_directory))
		{
			if (!e.is_regular_file())
				continue;

			m_texture = std::make_unique<sf::Texture>();
			m_texture->loadFromFile(e.path().string());
			auto key = e.path().lexically_relative(m_directory).string();
			m_textureViews.try_emplace(
				key,
				*m_texture,
				sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(m_texture->getSize()))
			);

			break;
		}
	}

	[[nodiscard]] const TextureView& TextureAtlas::getTextureView(const ResourcePath& path) const
	{
		auto key = path.fspath().string();
		return m_textureViews.at(key);
	}

}
