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

	level_preview->addRayGame(&rc_game);
	level_preview->move((float) Game::get().getView()->getSize().x / 2, 0);

}
