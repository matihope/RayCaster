//
// Created by mateusz on 8/29/23.
//

#ifndef RAYCASTER_SRC_SCENES_LEVEL2D_LEVEL2D_H_
#define RAYCASTER_SRC_SCENES_LEVEL2D_LEVEL2D_H_

#include "WorldEntity/WorldEntity.hpp"
#include "Rays/RayGame.h"
#include "SpriteBatch/SpriteBatch.hpp"
#include "Nodes/RectShape.hpp"
#include "Nodes/CircleShape.hpp"
#include "Nodes/RayShape.hpp"
#include "ViewArea.hpp"
#include "WorldEntity/BoxyWorldEntity.hpp"

class Level2D : public BoxyWorldEntity {
 public:
	Level2D();
	void addRayGame(rc::RayGame *game, Math::Vector2u maxSize);
	void onPhysicsUpdate(float dt) override;
	void setViewArea(const std::vector<std::pair<Math::Vector2f, float>> &hits);
	void setPlayerRadius(float radius);

 private:

	rc::RayGame *rc_game;
	SpriteBatch *sprites_preview;
	RectShape *background;
	CircleShape *player;
	RayShape *playerRay;
	ViewArea *viewArea;

	void _updateSpritePreview();
	void _updatePlayerPosition(float dt);
};

#endif //RAYCASTER_SRC_SCENES_LEVEL2D_LEVEL2D_H_
