//
// Created by mateusz on 8/29/23.
//

#ifndef RAYCASTER_LEVEL_H
#define RAYCASTER_LEVEL_H

#include "Math/Math.hpp"

namespace rc {

class Level {
 private:
	Math::Vector2u mapSize{}, tileSize{};
	std::vector<std::vector<int>> levelData{};
 public:
	Level(Math::Vector2u mapSize, Math::Vector2u tileSize);
	Level();

	void setSize(unsigned int width, unsigned int height);
	void setSize(Math::Vector2u newSize);
	void setTileSize(unsigned int width, unsigned int height);
	void setTileSize(Math::Vector2u newSize);
	void setBlock(Math::Vector2u position, int newState);
	bool readLevelFromFile(const std::string &path);
	const std::vector<std::vector<int>> &getLevelData() const;
	Math::Vector2u getSize();
};

} // rc

#endif //RAYCASTER_LEVEL_H
