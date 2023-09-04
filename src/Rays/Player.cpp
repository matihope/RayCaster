//
// Created by mateusz on 8/29/23.
//

#include <iostream>
#include "Player.h"

Player::Player() = default;

Math::Vector2f Player::getPosition() const {
	return position;
}
void Player::move(Math::Vector2f delta) {
	position += delta;
}

float Player::getDirectionRadians() const {
	return direction;
}

float Player::getDirectionDegrees() const {
	return (float) (direction / (2 * M_PI) * 360);
}

void Player::rotate(float radiansDiff) {
	direction += radiansDiff;
	direction = Math::makeInRange(direction, 2 * M_PI);
}
