//
// Created by mateusz on 8/28/23.
//

#ifndef RAYCASTER_WORLD_H
#define RAYCASTER_WORLD_H

#include "WorldEntity/WorldEntity.hpp"
#include "Rays/RayGame.h"
#include "Scenes/Level2D/Level2D.h"
#include "Scenes/Level3D/Level3D.hpp"

class World : public WorldEntity {
 public:
	World();
	void onUpdate(float dt) override;
 private:
	rc::RayGame rc_game;
	Level2D *level_preview;
	Level3D *level3D;
	float fov = Math::degreesToRadians(90.f);
};

#endif //RAYCASTER_WORLD_H
