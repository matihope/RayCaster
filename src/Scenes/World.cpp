//
// Created by mateusz on 8/28/23.
//

#include "World.h"
#include "Game/Game.hpp"

World::World() {
	Game::get().getRenderWindow().setSize(sf::Vector2u(2000, 1000));
	Game::get().getView()->setSize(1200, 600);

}
