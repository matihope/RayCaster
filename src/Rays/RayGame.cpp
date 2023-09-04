//
// Created by mateusz on 8/29/23.
//

#include "RayGame.h"
#include "JsonBridge/JsonBridge.hpp"
bool rc::RayGame::loadLevelFromFile(const std::string &levelPath) {
	if (!level.readLevelFromFile(levelPath))
		return false;

	JsonBridge bridge;
	bridge.load(levelPath);
	playerStartPos = {bridge.data["player_start"][0], bridge.data["player_start"][1]};

	return true;
}

Math::Vector2u rc::RayGame::getLevelSize() {
	return level.getSize();
}
const std::vector<std::vector<int>> &rc::RayGame::getLevelData() const {
	return level.getLevelData();
}
Math::Vector2f rc::RayGame::getPlayerPosition() const {
	return player.getPosition();
}
void rc::RayGame::movePlayer(Math::Vector2f delta) {
	auto playerPos = player.getPosition();

	auto diff = Math::Vector2f((playerRadius + 0.01) * Math::sign(delta.x), 0);
	if (checkCollision(playerPos + diff)) {
		delta.x = 0.0;
		while (!checkCollision(playerPos + diff))
			playerPos += diff;
	}

	diff = Math::Vector2f(0.f, (playerRadius + 0.01) * Math::sign(delta.y));
	if (checkCollision(playerPos + diff)) {
		delta.y = 0.0;
		while (!checkCollision(playerPos + diff))
			playerPos += diff;
	}

	player.move(delta);
}
void rc::RayGame::rotatePlayer(float deltaRadians) {
	player.rotate(deltaRadians);
}
float rc::RayGame::getPlayerRotation() const {
	return player.getDirectionRadians();
}
void rc::RayGame::setLevelTileSize(Math::Vector2f size) {
	level.setTileSize(size);
	player.setPosition(Math::Vector2f(size.x * playerStartPos.x, size.y * playerStartPos.y) + size / 2.f);
}
Math::Vector2f rc::RayGame::castRayFromPlayer(float directionRadians) const {
	return castRayFrom(player.getPosition(), directionRadians);
}
Math::Vector2f rc::RayGame::castRayFrom(Math::Vector2f position, float directionRadians) const {
	return level.castRayFrom(position, directionRadians);
}
Math::Vector2f rc::RayGame::getLevelTileSize() const {
	return level.getTileSize();
}
void rc::RayGame::setPlayerRadius(float radius) {
	playerRadius = radius;
}
bool rc::RayGame::checkCollision(Math::Vector2f position) const {
	auto newCoordsX = Math::Vector2i(position.x / level.getTileSize().x, position.y / level.getTileSize().y);
	return level.getLevelData()[newCoordsX.y][newCoordsX.x] == 1;
}
