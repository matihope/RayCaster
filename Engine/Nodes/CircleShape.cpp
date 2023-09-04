//
// Created by mateusz on 8/30/23.
//

#include "CircleShape.hpp"
CircleShape::CircleShape(sf::Color myColor, float radius) {
	circle.setFillColor(myColor);
	setRadius(radius);
}
void CircleShape::onDraw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(circle, states);
}
void CircleShape::setRadius(float radius) {
	circle.setRadius(radius);
	circle.move(-radius, -radius);
}
float CircleShape::getRadius() const {
	return circle.getRadius();
}
