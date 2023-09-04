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

class Level2D : public WorldEntity {
 public:
	Level2D();
	void addRayGame(rc::RayGame *game);
	void onPhysicsUpdate(float dt) override;

	void setViewArea(std::vector<Math::Vector2f> vector_1);

	void onDraw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void setPlayerRadius(float radius);
 private:

	rc::RayGame *rc_game;
	SpriteBatch *sprites_preview;
	RectShape *background;
	CircleShape *player;
	RayShape *playerRay;

	sf::VertexArray viewArea;
	const sf::Texture *viewTexture;

	void _updateSpritePreview();
	void _updatePlayerPosition(float dt);
};

#endif //RAYCASTER_SRC_SCENES_LEVEL2D_LEVEL2D_H_
