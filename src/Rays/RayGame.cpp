//
// Created by mateusz on 8/29/23.
//

#include <iostream>
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

Math::Vector2u rc::RayGame::getLevelSize() const {
  return level.getSize();
}
const std::vector<std::vector<int>> &rc::RayGame::getLevelData() const {
  return level.getLevelData();
}
Math::Vector2f rc::RayGame::getPlayerPosition() const {
  return player.getPosition();
}
void rc::RayGame::movePlayer(Math::Vector2f delta) {
  auto initial = player.getPosition();
  auto playerPos = player.getPosition();
  float step = 1.f / 64.f;

  Math::Vector2f deltaX(delta.x, 0.f);
  if (checkCollision(playerPos + deltaX)) {
    while (!checkCollision(playerPos + normalizeVector(deltaX)))
      playerPos += normalizeVector(deltaX);
    delta.x = 0.0;
  }

  Math::Vector2f deltaY(0.f, delta.y);
  if (checkCollision(playerPos + deltaY)) {
    while (!checkCollision(playerPos + normalizeVector(deltaY)))
      playerPos += normalizeVector(deltaY);
    delta.y = 0.0;
  }

  player.setPosition(playerPos + delta);
//  if (checkCollision(player.getPosition())) {
//    std::cout << "WTF" << std::endl;
//    player.setPosition(initial);
//  }
}

void rc::RayGame::rotatePlayer(float deltaRadians) {
  player.rotate(deltaRadians);
}

float rc::RayGame::getPlayerRotation() const {
  return player.getDirectionRadians();
}

void rc::RayGame::setLevelTileSize(Math::Vector2f size) {
  level.setTileSize(size);
  player.setPosition(
      Math::Vector2f(size.x * static_cast<float>(playerStartPos.x), size.y * static_cast<float>(playerStartPos.y))
          + size / 2.f);
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

bool isCircleInsideSquare(Math::Vector2f topLeft, Math::Vector2f playerPos, float playerRadius) {
  if (playerPos.x + playerRadius < topLeft.x)
    return false;
  if (playerPos.x - playerRadius > topLeft.x + 1)
    return false;
  if (playerPos.y - playerRadius > topLeft.y + 1)
    return false;
  if (playerPos.y + playerRadius < topLeft.y)
    return false;
  return true;
}

bool rc::RayGame::checkCollision(Math::Vector2f position) const {
  Math::Vector2f pos = position / getLevelTileSize();
  Math::Vector2i rectPos((int) std::round(pos.x), (int) std::round(pos.y));
  float radius = playerRadius / getLevelTileSize().x;

  if (rectPos.x - 1 >= 0 && rectPos.y - 1 >= 0 && getLevelData()[rectPos.y - 1][rectPos.x - 1] == 1) {
    if (isCircleInsideSquare((rectPos + Math::Vector2i(-1, -1)).type<float>(), pos, radius))
      return true;
  }
  if (rectPos.x - 1 >= 0 && rectPos.y < getLevelSize().y && getLevelData()[rectPos.y][rectPos.x - 1] == 1) {
    if (isCircleInsideSquare((rectPos + Math::Vector2i(-1, 0)).type<float>(), pos, radius))
      return true;
  }
  if (rectPos.y - 1 >= 0 && rectPos.x < getLevelSize().x && getLevelData()[rectPos.y - 1][rectPos.x] == 1) {
    if (isCircleInsideSquare((rectPos + Math::Vector2i(0, -1)).type<float>(), pos, radius))
      return true;
  }
  if (rectPos.x < getLevelSize().x && rectPos.y < getLevelSize().y && getLevelData()[rectPos.y][rectPos.x] == 1) {
    if (isCircleInsideSquare(rectPos.type<float>(), pos, radius))
      return true;
  }

  return false;
}

std::vector<std::pair<Math::Vector2f, float>> rc::RayGame::castRaysFromPlayer(float fovRadians,
                                                                              unsigned int numRays) const {
  std::vector<std::pair<Math::Vector2f, float>> hits;

  std::vector<float> diffs;
  float angle = fovRadians / 2.f;
  for (int i = 0; i < numRays; i++) {
    float fraction = ((float) numRays / 2.f - (float) i + 1.f) / ((float) numRays / 2.f);
    diffs.push_back(angle - std::atan(fraction * std::tan(fovRadians / 2.f)));
    angle -= diffs.back();
  }

  float direction = getPlayerRotation() - fovRadians / 2.f;
  for (int i = 0; i < numRays; i++) {
    hits.emplace_back(castRayFromPlayer(direction), direction);
    direction += diffs[i];
  }
  return std::move(hits);
}
