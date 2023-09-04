//
// Created by mateusz on 8/29/23.
//

#include "Level2D.h"
#include "ResourceManager/ResourceManager.hpp"
#include "Game/Game.hpp"

Level2D::Level2D() {
	rc_game = nullptr;
	background = addChild<RectShape>(sf::Color(50, 50, 50), sf::Vector2f(600, 600));
	sprites_preview = addChild<SpriteBatch>();
	playerRay = addChild<RayShape>(sf::Color(210, 210, 250), 3.5f, 45.f, 12.f);
	mouseRay = addChild<RayShape>(sf::Color(210, 10, 250), 3.5f, 45.f, 12.f);
	player = addChild<CircleShape>(sf::Color(70, 70, 170), 10.f);
	collisionPoint = addChild<CircleShape>(sf::Color(50, 255, 50), 5.f);
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
	sprites_preview->setTexture(&ResourceManager::get().getTexture("resources/colors.png"));

	for (int y = 0; y < level_height; y++) {
		for (int x = 0; x < level_width; x++) {
			QuickSprite sprite = sprites_preview->getSprite(y * level_width + x);
			auto [tex_x, tex_y] = sprites_preview->getTexture()->getSize();
			if (rc_game->getLevelData()[y][x] == 1) {
				sprite.setTexPosition(sf::Vector2f(tex_x / 5.f, 0));
				sprite.setTexSize({tex_x / 5.f, (float) tex_y});
			} else {
				sprite.setTexSize({0, 0});
			}
		}
	}

	rc_game->setLevelTileSize(600 / 6.f);
}

void Level2D::_updateSpritePreview() {
	auto [level_width, level_height] = rc_game->getLevelSize();
	for (int y = 0; y < level_height; y++) {
		for (int x = 0; x < level_width; x++) {
			QuickSprite sprite = sprites_preview->getSprite(y * level_width + x);
			auto [tex_x, tex_y] = sprites_preview->getTexture()->getSize();
			if (rc_game->getLevelData()[y][x] == 1) {
				sprite.setTexPosition(sf::Vector2f(tex_x / 5.f, 0));
				sprite.setTexSize({tex_x / 5.f, (float) tex_y});
			} else {
				sprite.setTexSize({0, 0});
			}
		}
	}
}
void Level2D::_updatePlayerPosition(float dt) {
	float
		deltaRotation = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	rc_game->rotatePlayer(deltaRotation * dt * 3.0);
	auto playerRotation = rc_game->getPlayerRotation();
	playerRay->setRotation(Math::radiansToDegrees(playerRotation));

	auto delta_x = sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	auto delta_y = sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	auto delta = Math::Vector2f(delta_x, delta_y);
	delta = Math::normalizeVector(delta);
	delta = Math::rotateVector(delta, playerRotation);
	delta *= 100 * dt;

	rc_game->movePlayer(delta);

	auto [player_x, player_y] = rc_game->getPlayerPosition();
	playerRay->setPosition(player_x, player_y);
	player->setPosition(player_x, player_y);

	mouseRay->setPosition(player_x, player_y);
	mouseRay->pointAt(Game::get().getMousePos() - player->getGlobalPosition());

	auto [collision_x, collision_y] = rc_game->castRayFromPlayer(Math::degreesToRadians(mouseRay->getRotation() - 180.f));
	collisionPoint->setPosition(collision_x, collision_y);
}
