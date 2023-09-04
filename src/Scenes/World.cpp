//
// Created by mateusz on 8/28/23.
//

#include "World.h"
#include "Game/Game.hpp"

World::World() {
	Game::get().getRenderWindow().setSize(sf::Vector2u(2000, 1000));
	Game::get().setViewportSize({1200, 600});

	level_preview = addChild<Level2D>();
	rc_game.loadLevelFromFile("world.json");
	rc_game.setPlayerRadius(10.f);
	level_preview->setPlayerRadius(10.f);

	level_preview->addRayGame(&rc_game);
	level_preview->move((float) Game::get().getView()->getSize().x / 2, 0);

	level3D = addChild<Level3D>();
	level3D->addRayGame(&rc_game);

}
void World::onUpdate(float dt) {
	std::vector<Math::Vector2f> hits;
	float fov = Math::degreesToRadians(90.f);
	float direction = rc_game.getPlayerRotation() - Math::degreesToRadians(180.f) - fov / 2.f;

	int width = 600;
	for (int i = 0; i < width; i++) {
		hits.push_back(rc_game.castRayFromPlayer(direction));
		direction += fov / width;
	}

	level3D->setBars(hits, fov);

	level_preview->setViewArea(hits);
}
