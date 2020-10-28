#ifndef GROUP_H
#define GROUP_H

#include "Container.h"

namespace ire::core::widgets
{
	struct Group : Container
	{
		Group(const sf::Vector2f& size);

		static std::unique_ptr<Group> create(const sf::Vector2f& size);

		void setSize(const sf::Vector2f& size) override;

		sf::Vector2f getInnerSize() const override;

		sf::Vector2f getChildWidgetOffset() const override;

		void draw(sf::RenderTarget& target) override;

		void init();
		static const WidgetType m_type;
		const WidgetType getType() const override
		{
			return m_type;
		}

	protected:
	};
}
#endif // !GROUP_H
