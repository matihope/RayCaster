//
// Created by mateusz on 8/29/23.
//

#include <string>
#include "Level.h"
#include "JsonBridge/JsonBridge.hpp"

namespace rc {
Level::Level() : Level({0, 0}, {1, 1}) {

}

Level::Level(Math::Vector2u mapSize, Math::Vector2u tileSize) {
	setSize(mapSize);
	setTileSize(tileSize);
}

void Level::setSize(unsigned int width, unsigned int height) {
	mapSize = Math::Vector2u(width, height);
	levelData.resize(height, std::vector<int>(width, 0));
}

void Level::setSize(Math::Vector2u newSize) {
	setSize(newSize.x, newSize.y);
}

void Level::setTileSize(unsigned int width, unsigned int height) {
	tileSize = Math::Vector2u(width, height);
}

void Level::setTileSize(Math::Vector2u newSize) {
	setTileSize(newSize.x, newSize.y);
}

void Level::setBlock(Math::Vector2u position, int newState) {
	if (position.x < mapSize.x && position.y < mapSize.y)
		levelData[position.y][position.x] = newState;
}

bool Level::readLevelFromFile(const std::string &path) {
	JsonBridge fileData;
	if (!fileData.load(path))
		return false;

	setSize(fileData.data["data"].size(), fileData.data["data"][0].size());
	for (unsigned int y = 0; y < fileData.data["data"].size(); y++) {
		for (unsigned int x = 0; x < fileData.data["data"][y].size(); x++) {
			setBlock({x, y}, fileData.data["data"][y][x]);
		}
	}

	return true;
}

Math::Vector2u Level::getSize() {
	return mapSize;
}
const std::vector<std::vector<int>> &Level::getLevelData() const {
	return levelData;
}

float getRayLengthFrom(Math::Vector2f position, float directionRads) {
	return 0.0;
}

} // rc
