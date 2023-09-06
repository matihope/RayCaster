//
// Created by mateusz on 8/28/23.
//

#include "World.h"
#include "Game/Game.hpp"

World::World() {
	Game::get().getRenderWindow().setSize(sf::Vector2u(2000, 1000));
	Game::get().setViewportSize({1200, 600});

	level_preview = addChild<Level2D, 1>();
	rc_game.loadLevelFromFile("world.json");
	rc_game.setLevelTileSize({64.f, 64.f});
	rc_game.setPlayerRadius(10.f);

	level_preview->setPlayerRadius(10.f);
	level_preview->addRayGame(&rc_game, {64 * rc_game.getLevelSize().x, 64 * rc_game.getLevelSize().y});
	level_preview->setScale(0.4, 0.4);
	level_preview->move({1200, 600});

	level3D = addChild<Level3D>();
	level3D->addRayGame(&rc_game, {1200.f, 600.f});
}

void World::onUpdate(float dt) {

	// point of collision, direction at which the ray was sent
	std::vector<std::pair<Math::Vector2f, float>> hits;

	fov += dt * (sf::Keyboard::isKeyPressed(sf::Keyboard::I) - sf::Keyboard::isKeyPressed(sf::Keyboard::K));
//	std::cout << "Fov: " << fov << std::endl;

	hits = rc_game.castRaysFromPlayer(fov, 1200);

	level3D->setBars(hits, fov);
	level_preview->setViewArea(hits);
}
