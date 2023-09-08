//
// Created by mateusz on 8/31/23.
//

#ifndef RAYCASTER_SRC_SCENES_LEVEL3D_HPP_
#define RAYCASTER_SRC_SCENES_LEVEL3D_HPP_

#include "WorldEntity/WorldEntity.hpp"
#include "RayGame.h"
#include "SpriteBatch/SpriteBatch.hpp"
#include "Nodes/RectShape.hpp"
#include "WorldEntity/BoxyWorldEntity.hpp"
class Level3D : public BoxyWorldEntity {
 public:
	void addRayGame(rc::RayGame *game, Math::Vector2f size);
	void setBars(const std::vector<std::pair<Math::Vector2f, float>> &lengths, float fov);
	Math::Vector2f getEntitySize() const;
	Level3D();
 private:
	rc::RayGame *rc_game;
	Math::Vector2f entitySize{};
	SpriteBatch *verticalBars;
	RectShape *floor, *sky;
};

#endif //RAYCASTER_SRC_SCENES_LEVEL3D_HPP_
