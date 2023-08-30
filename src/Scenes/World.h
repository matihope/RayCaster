//
// Created by mateusz on 8/28/23.
//

#ifndef RAYCASTER_WORLD_H
#define RAYCASTER_WORLD_H

#include "WorldEntity/WorldEntity.hpp"
#include "Rays/RayGame.h"
#include "Scenes/Level2D/Level2D.h"

class World : public WorldEntity {
 public:
	World();
 private:
	rc::RayGame rc_game;
	Level2D *level_preview;
};

#endif //RAYCASTER_WORLD_H
