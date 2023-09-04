//
// Created by mateusz on 8/29/23.
//

#include "RayGame.h"
bool rc::RayGame::loadLevelFromFile(const std::string &levelPath) {
	return level.readLevelFromFile(levelPath);
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
	player.move(delta);
}
void rc::RayGame::rotatePlayer(float deltaRadians) {
	player.rotate(deltaRadians);
}
float rc::RayGame::getPlayerRotation() const {
	return player.getDirectionRadians();
}
void rc::RayGame::setLevelTileSize(float size) {
	level.setTileSize({size, size});
}
Math::Vector2f rc::RayGame::castRayFromPlayer(float directionRadians) const {
	return castRayFrom(player.getPosition(), directionRadians);
}
Math::Vector2f rc::RayGame::castRayFrom(Math::Vector2f position, float directionRadians) const {
	return level.castRayFrom(position, directionRadians);
}
