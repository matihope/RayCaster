//
// Created by mateusz on 8/29/23.
//

#ifndef RAYCASTER_PLAYER_H
#define RAYCASTER_PLAYER_H

#include "Math/Math.hpp"
class Player {
 public:
	Player();
	[[nodiscard]] Math::Vector2f getPosition() const;
	[[nodiscard]] float getDirectionRadians() const;
	void move(Math::Vector2f delta);
	void rotate(float radiansDiff);
 private:
	Math::Vector2f position;
	float direction{};
	float getDirectionDegrees() const;
};

#endif //RAYCASTER_PLAYER_H
