//
// Created by mateusz on 8/29/23.
//

#ifndef RAYCASTER_SRC_RAYS_RAYGAME_H_
#define RAYCASTER_SRC_RAYS_RAYGAME_H_

#include <string>
#include "Level.h"
#include "Player.h"

namespace rc {
class RayGame {
 public:
	bool loadLevelFromFile(const std::string &levelPath);
	Math::Vector2u getLevelSize();
	const std::vector<std::vector<int>> &getLevelData() const;

	void movePlayer(Math::Vector2f delta);
	Math::Vector2f getPlayerPosition() const;
 private:
	Level level;
	Player player;
};
}

#endif //RAYCASTER_SRC_RAYS_RAYGAME_H_
