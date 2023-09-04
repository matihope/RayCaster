//
// Created by mateusz on 8/29/23.
//

#ifndef RAYCASTER_SRC_RAYS_RAYGAME_H_
#define RAYCASTER_SRC_RAYS_RAYGAME_H_

#include <string>
#include "Level/Level.h"
#include "Player.h"

namespace rc {
class RayGame {
 public:
	bool loadLevelFromFile(const std::string &levelPath);
	Math::Vector2u getLevelSize();
	[[nodiscard]] const std::vector<std::vector<int>> &getLevelData() const;

	void setPlayerRadius(float radius);

	void movePlayer(Math::Vector2f delta);
	void rotatePlayer(float deltaRadians);

	[[nodiscard]] Math::Vector2f getPlayerPosition() const;
	[[nodiscard]] float getPlayerRotation() const;

	void setLevelTileSize(Math::Vector2f size);
	[[nodiscard]] Math::Vector2f getLevelTileSize() const;

	[[nodiscard]] Math::Vector2f castRayFromPlayer(float directionRadians) const;
	[[nodiscard]] Math::Vector2f castRayFrom(Math::Vector2f position, float directionRadians) const;

	[[nodiscard]] bool checkCollision(Math::Vector2f position) const;

 private:
	Level level;
	Player player;
	float playerRadius{};
	Math::Vector2i playerStartPos;
};
}

#endif //RAYCASTER_SRC_RAYS_RAYGAME_H_
