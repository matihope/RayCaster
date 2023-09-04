//
// Created by mateusz on 8/29/23.
//

#include <string>
#include <iostream>
#include <set>
#include "Level.h"
#include "JsonBridge/JsonBridge.hpp"

namespace rc {
Level::Level() : Level({0, 0}, {1, 1}) {

}

Level::Level(Math::Vector2u mapSize, Math::Vector2f tileSize) {
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

void Level::setTileSize(float width, float height) {
	levelWalls.clear();
	tileSize = Math::Vector2f(width, height);
	for (int y = 0; y < levelData.size(); y++) {
		for (int x = 0; x < levelData[0].size(); x++) {
			if (levelData[y][x] != 0) {
				auto c1 = Math::Vector2f(x * width, y * height);
				auto c2 = c1 + Math::Vector2f(width, 0);
				auto c3 = c2 + Math::Vector2f(0, height);
				auto c4 = c1 + Math::Vector2f(0, height);
				levelWalls.push_back({levelData[y][x], c1, c2});
				levelWalls.push_back({levelData[y][x], c2, c3});
				levelWalls.push_back({levelData[y][x], c3, c4});
				levelWalls.push_back({levelData[y][x], c4, c1});
			}
		}
	}
}

void Level::setTileSize(Math::Vector2f newSize) {
	setTileSize(newSize.x, newSize.y);
}

void Level::setBlock(Math::Vector2u position, int newState) {
	if (0 <= position.x && position.x < mapSize.x && 0 <= position.y && position.y < mapSize.y)
		levelData[position.y][position.x] = newState;
}

bool Level::readLevelFromFile(const std::string &path) {
	JsonBridge fileData;
	if (!fileData.load(path))
		return false;

	setSize(fileData.data["data"].size(), fileData.data["data"][0].get<std::string>().size());
	for (unsigned int y = 0; y < fileData.data["data"].size(); y++) {
		const std::string &row = fileData.data["data"][y].get<std::string>();
		for (unsigned int x = 0; x < row.size(); x++)
			setBlock({x, y}, row[x] - '0');
	}

	return true;
}

Math::Vector2u Level::getSize() {
	return mapSize;
}
const std::vector<std::vector<int>> &Level::getLevelData() const {
	return levelData;
}

auto intersectionComparator = [](const std::pair<Math::Vector2f, float> &a, const std::pair<Math::Vector2f, float> &b) {
	return a.second < b.second;
};

Math::Vector2<float> Level::castRayFrom(Math::Vector2f position, float angleRadians) const {
	auto maxLength = std::max(tileSize.x * levelData[0].size(), tileSize.y * levelData.size());
	Math::Vector2f infiniteRay = {0, maxLength};
	infiniteRay = Math::rotateVector(infiniteRay, angleRadians);
	infiniteRay += position;

	std::set<std::pair<Math::Vector2f, float>, decltype(intersectionComparator)> intersections;
	for (const auto &wall : levelWalls) {
		if (Math::doLinesIntersect(wall.start, wall.end, position, infiniteRay)) {
			auto intersection = Math::findLineIntersection(wall.start, wall.end, position, infiniteRay);
			intersections.insert({intersection, (intersection - position).length()});
		}
	}
	return intersections.begin()->first;
}
Math::Vector2f Level::getTileSize() const {
	return tileSize;
}

} // rc
