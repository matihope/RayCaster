//
// Created by mateusz on 8/29/23.
//

#include "Level2D.h"
#include "ResourceManager/ResourceManager.hpp"
#include "Game/Game.hpp"

Level2D::Level2D() {
	rc_game = nullptr;
	background = addChild<RectShape>(sf::Color(73, 88, 103), sf::Vector2f(600, 600));
	sprites_preview = addChild<SpriteBatch>();
	viewArea = addChild<ViewArea>();
	playerRay = addChild<RayShape>(sf::Color(87, 115, 173), 3.5f, 45.f, 12.f);
	player = addChild<CircleShape>(sf::Color(254, 95, 85), 1.f);

}
void Level2D::onPhysicsUpdate(float dt) {
	_updateSpritePreview();
	_updatePlayerPosition(dt);
}

void Level2D::addRayGame(rc::RayGame *game) {
	rc_game = game;
	auto [view_width, view_height] = Game::get().getViewportSize();
	view_width /= 2;
	auto [level_width, level_height] = game->getLevelSize();
	sprites_preview->makeGrid({level_width, level_height},
	                          sf::Vector2f(view_width / level_width, view_height / level_height));
	sprites_preview->setTexture(&ResourceManager::get().getTexture("resources/Castle_Wall.png"));

	rc_game->setLevelTileSize({64.f, 64.f});
}

void Level2D::_updateSpritePreview() {
	auto [level_width, level_height] = rc_game->getLevelSize();
	auto [tex_x, tex_y] = sprites_preview->getTexture()->getSize();
	for (int y = 0; y < level_height; y++) {
		for (int x = 0; x < level_width; x++) {
			QuickSprite sprite = sprites_preview->getSprite(y * level_width + x);
			if (rc_game->getLevelData()[y][x] == 1) {
				sprite.setTexSize(sf::Vector2f(tex_x, tex_y));
			} else {
				sprite.setTexSize({0, 0});
			}
		}
	}
}
Math::Vector2f scalePosition(const Math::Vector2f &position, rc::RayGame *rc_game) {
	auto [view_width, view_height] = Game::get().getViewportSize();
	view_width /= 2;
	auto [level_width, level_height] = rc_game->getLevelSize();
	auto [tile_width, tile_height] = rc_game->getLevelTileSize();
	return Math::Vector2f(position.x / tile_width * view_width / level_width,
	                      position.y / tile_height * view_height / level_height);
}

void Level2D::_updatePlayerPosition(float dt) {
	float
		deltaRotation = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	rc_game->rotatePlayer(deltaRotation * dt);
	auto playerRotation = rc_game->getPlayerRotation() - Math::degreesToRadians(180.f);
	playerRay->setRotation(Math::radiansToDegrees(playerRotation));

	auto delta_x = sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	auto delta_y = sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	auto delta = Math::Vector2f(delta_x, delta_y);
	delta = Math::normalizeVector(delta);
	delta = Math::rotateVector(delta, playerRotation);
	delta *= 60 * dt;

	rc_game->movePlayer(delta);

	auto [player_x, player_y] = scalePosition(rc_game->getPlayerPosition(), rc_game);
	playerRay->setPosition(player_x, player_y);
	player->setPosition(player_x, player_y);
}

void Level2D::setViewArea(const std::vector<std::pair<Math::Vector2f, float>> &hits) {
	std::vector<std::pair<Math::Vector2f, float>> scaledHits;

	for (const auto &hit : hits)
		scaledHits.emplace_back(scalePosition(hit.first, rc_game), hit.second);

	viewArea->setViewArea(scaledHits, player->getPosition());
}

void Level2D::setPlayerRadius(float radius) {
	player->setRadius(radius);
}
