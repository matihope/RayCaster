//
// Created by mateusz on 8/31/23.
//

#include <iostream>
#include "RayShape.hpp"
#include "Math/Math.hpp"

RayShape::RayShape(sf::Color color, float width, float length, float wingLength) {
	setColor(color);
	setSize(width, length, wingLength);
}

void RayShape::onDraw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(body, states);
	target.draw(leftWing, states);
	target.draw(rightWing, states);
	target.draw(arrowFill, states);
}

void RayShape::setSize(float width, float length, float wingLength) {
	this->width = width;
	this->length = length;
	this->wingLength = wingLength;

	body.setSize({width, length});
	body.setOrigin({width / 2, 0});
	body.setPosition({0, -length});

	leftWing.setOrigin({width / 2, 0});
	leftWing.setSize({width, wingLength});
	leftWing.setPosition({0, -length});
	leftWing.setRotation(-35.f);

	rightWing.setOrigin({width / 2, 0});
	rightWing.setSize({width, wingLength});
	rightWing.setPosition({0, -length});
	rightWing.setRotation(35.f);

	arrowFill.setOrigin(width / 2, width / 2);
	arrowFill.setPosition({0, -length});
	arrowFill.setRadius(width / 2);
}
void RayShape::setColor(sf::Color color) {
	body.setFillColor(color);
	leftWing.setFillColor(color);
	rightWing.setFillColor(color);
	arrowFill.setFillColor(color);
}

void RayShape::pointAt(sf::Vector2f arrowHead) {
	float newLen = sqrtf(arrowHead.x * arrowHead.x + arrowHead.y * arrowHead.y);
	setSize(width, newLen, wingLength);
	auto angle = (float) atan(arrowHead.y / arrowHead.x);
	angle = Math::radiansToDegrees(angle);
	angle += 90.f;
	if (arrowHead.x < 0)
		angle += 180.;

	setRotation(angle);
}
