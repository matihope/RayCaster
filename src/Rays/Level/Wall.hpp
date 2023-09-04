//
// Created by mateusz on 9/2/23.
//

#ifndef RAYCASTER_SRC_RAYS_LEVEL_WALL_HPP_
#define RAYCASTER_SRC_RAYS_LEVEL_WALL_HPP_

#include "Math/Math.hpp"
class Wall {
 public:
	int wallType;
	Math::Vector2f start, end;
};

#endif //RAYCASTER_SRC_RAYS_LEVEL_WALL_HPP_
