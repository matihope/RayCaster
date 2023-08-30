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
	void move(Math::Vector2f delta);
 private:
	Math::Vector2f position;
};

#endif //RAYCASTER_PLAYER_H
