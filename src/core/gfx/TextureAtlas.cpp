#include "TextureAtlas.h"

#include <algorithm>
#include <tuple>
#include <vector>
#include <utility>

namespace ire::core::gfx
{

	std::vector<std::pair<int, sf::IntRect>> tryPackRectangles(std::vector<sf::Vector2i> sizes, const sf::Vector2i& binSize, int padding)
	{
		// TODO: better implementation. This is a very naive guilottine algorithm.

		std::sort(sizes.begin(), sizes.end(), [](auto& lhs, auto& rhs) {
			auto lhsSize = lhs.x * lhs.y;
			auto rhsSize = rhs.x * rhs.y;
			return lhsSize > rhsSize;
		});

		for (auto& size : sizes)
		{
			size.x += padding;
			size.y += padding;
		}

		std::vector<std::pair<int, sf::IntRect>> packing;
		packing.reserve(sizes.size());
		std::vector<sf::IntRect> availableSpace;
		availableSpace.emplace_back(sf::Vector2i(0, 0), binSize);

		auto findSpace = [&availableSpace](sf::Vector2i size) {
			auto begin = availableSpace.begin();
			auto bestFit = availableSpace.end();
			int bestFitSize = std::numeric_limits<int>::max();

			for (; begin != availableSpace.end(); ++begin)
			{
				auto& space = *begin;
				if (space.width >= size.x && space.height >= size.y)
				{
					const int size = space.width * space.height;
					if (size < bestFitSize)
					{
						bestFit = begin;
						bestFitSize = size;
					}
				}
			}

			return bestFit;
		};

		auto insertRect = [&](int i, typename std::vector<sf::IntRect>::iterator j) {
			auto space = *j;
			auto size = sizes[i];
			sf::IntRect rect(space.left, space.top, size.x - padding, size.y - padding);

			packing.emplace_back(i, rect);
			availableSpace.erase(j);
			availableSpace.emplace_back(space.left, space.top + size.y, space.width, space.height - size.y);
			availableSpace.emplace_back(space.left + size.x, space.top, space.width - space.left, space.height - size.y);
		};

		for (int i = 0; i < sizes.size(); ++i)
		{
			auto& size = sizes[i];
			auto it = findSpace(size);
			if (it == availableSpace.end())
			{
				continue;
			}

			insertRect(i, it);
		}

		return packing;
	}

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
		std::vector<std::pair<std::string, sf::Texture>> parts;
		for (auto& e : std::filesystem::recursive_directory_iterator(m_directory))
		{
			if (!e.is_regular_file())
				continue;

			sf::Texture tex{};
			tex.loadFromFile(e.path().string());
			auto key = e.path().lexically_relative(m_directory).string();
			parts.emplace_back(key, std::move(tex));
		}

		std::vector<sf::Vector2i> sizes;
		for (auto& [key, tex] : parts)
		{
			sizes.emplace_back(tex.getSize());
		}

		sf::Vector2i binSize(256, 256);
		std::vector<std::pair<int, sf::IntRect>> packing;
		for (int i = 0; i < 4; ++i)
		{
			packing = tryPackRectangles(sizes, binSize, padding);
			if (packing.size() == parts.size())
			{
				break;
			}

			binSize *= 2;
		}

		if (packing.size() != parts.size())
		{
			throw std::runtime_error("Couldn't pack sprites...\n");
		}

		m_texture = std::make_unique<sf::Texture>();
		m_texture->create(binSize.x, binSize.y);

		for (auto& [i, rect] : packing)
		{
			auto& [key, tex] = parts[i];
			m_texture->update(tex, rect.left, rect.top);

			m_textureViews.try_emplace(
				key,
				*m_texture,
				sf::FloatRect(rect)
			);
		}
	}

	[[nodiscard]] const TextureView& TextureAtlas::getTextureView(const ResourcePath& path) const
	{
		auto key = path.fspath().string();
		return m_textureViews.at(key);
	}

}
