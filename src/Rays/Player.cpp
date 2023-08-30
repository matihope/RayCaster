//
// Created by mateusz on 8/29/23.
//

#include "Player.h"

Player::Player() = default;

Math::Vector2f Player::getPosition() const {
	return position;
}
void Player::move(Math::Vector2f delta) {
	position += delta;
}
