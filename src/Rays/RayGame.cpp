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
