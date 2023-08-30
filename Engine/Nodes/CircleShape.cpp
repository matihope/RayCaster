//
// Created by mateusz on 8/30/23.
//

#include "CircleShape.hpp"
CircleShape::CircleShape(sf::Color myColor, float radius) {
	circle.setFillColor(myColor);
	circle.setRadius(radius);
	circle.move(-radius, -radius);
}
void CircleShape::onDraw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(circle, states);
}
