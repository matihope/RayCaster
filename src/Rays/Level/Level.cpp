//
// Created by mateusz on 8/29/23.
//

#include <string>
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
        auto c1 = Math::Vector2f((float) x * width, (float) y * height);
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

  setSize(fileData.data["data"][0].get<std::string>().size(), fileData.data["data"].size());
  for (unsigned int y = 0; y < levelData.size(); y++) {
    const std::string &row = fileData.data["data"][y].get<std::string>();
    for (unsigned int x = 0; x < row.size(); x++)
      setBlock({x, y}, row[x] - '0');
  }

  return true;
}

Math::Vector2u Level::getSize() const {
  return mapSize;
}

const std::vector<std::vector<int>> &Level::getLevelData() const {
  return levelData;
}

Math::Vector2f Level::castRayFrom(Math::Vector2f position, float angleRadians) const {
  // Ray Casting implemented using the DDA algorithm.

  position /= getTileSize();

  Math::Vector2f dirVec = Math::rotateVector(Math::Vector2f(1.f, 0), angleRadians);
  Math::Vector2i intPos((int) position.x, (int) position.y);
  Math::Vector2f step = {dirVec.y / dirVec.x, dirVec.x / dirVec.y};
  Math::Vector2f stepLength = {std::sqrt(step.x * step.x + 1), std::sqrt(step.y * step.y + 1)};
  Math::Vector2f rayProgress = {0, 0};

  rayProgress.x = dirVec.x > 0 ? (float) (intPos.x + 1) - position.x : position.x - (float) (intPos.x);
  rayProgress.y = dirVec.y > 0 ? (float) (intPos.y + 1) - position.y : position.y - (float) (intPos.y);
  rayProgress *= stepLength;

  float maxDistance = std::max(getSize().x, getSize().y) * 1.42f;
  float distance = 0;
  bool foundCollision = false;
  while (!foundCollision && distance < maxDistance) {
    if (rayProgress.x < rayProgress.y) {
      intPos.x += Math::sign(dirVec.x);
      distance = rayProgress.x;
      rayProgress.x += stepLength.x;
    } else {
      intPos.y += Math::sign(dirVec.y);
      distance = rayProgress.y;
      rayProgress.y += stepLength.y;
    }
    if (0 <= intPos.x && intPos.x < getSize().x && 0 <= intPos.y && intPos.y < getSize().y) {
      if (levelData[intPos.y][intPos.x] == 1) {
        foundCollision = true;
      }
    }
  }

  if (foundCollision) return (position + dirVec * distance) * getTileSize();
  return {0.f, 0.f};
}

Math::Vector2f Level::getTileSize() const {
  return tileSize;
}

} // rc
