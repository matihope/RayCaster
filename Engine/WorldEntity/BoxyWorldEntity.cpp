//
// Created by mateusz on 9/6/23.
//

#include "BoxyWorldEntity.hpp"
void BoxyWorldEntity::setMaxRenderSize(Math::Vector2u newSize) {
	this->maxSize = newSize;
}
Math::Vector2u BoxyWorldEntity::getMaxSize() const {
	return maxSize;
}

void BoxyWorldEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (!m_show) return;
	if (maxSize.x == 0 && maxSize.y == 0) {
		renderOnto(target, states);
	} else {
		sf::RenderTexture texture;
		texture.create(maxSize.x, maxSize.y);
		states.transform *= getInverseTransform();
		renderOnto(texture, states);
		states.transform *= getTransform();
		states.transform *= getTransform();
		texture.display();

		sf::Sprite sprite;
		sprite.setTexture(texture.getTexture());
		target.draw(sprite, states);
	}
}
void BoxyWorldEntity::setMaxRenderSize(unsigned int width, unsigned int height) {
	setMaxRenderSize({width, height});
}
