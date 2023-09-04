//
// Created by mateusz on 8/31/23.
//

#ifndef RAYCASTER_SRC_SCENES_LEVEL3D_HPP_
#define RAYCASTER_SRC_SCENES_LEVEL3D_HPP_

#include "WorldEntity/WorldEntity.hpp"
#include "RayGame.h"
#include "SpriteBatch/SpriteBatch.hpp"
#include "Nodes/RectShape.hpp"
class Level3D : public WorldEntity {
 public:
	void addRayGame(rc::RayGame *game);
	void setBars(std::vector<Math::Vector2f> lengths, float fov);
	Level3D();
 private:
	rc::RayGame *rc_game;
	SpriteBatch *verticalBars;
	RectShape *floor;
};

#endif //RAYCASTER_SRC_SCENES_LEVEL3D_HPP_
