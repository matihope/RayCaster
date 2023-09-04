//
// Created by mateusz on 8/29/23.
//

#ifndef RAYCASTER_LEVEL_H
#define RAYCASTER_LEVEL_H

#include "Math/Math.hpp"
#include "Wall.hpp"

namespace rc {

class Level {
 private:
	Math::Vector2u mapSize{};
	Math::Vector2f tileSize{};
	std::vector<std::vector<int>> levelData{};
	std::vector<Wall> levelWalls{};
 public:
	Level(Math::Vector2u mapSize, Math::Vector2f tileSize);
	Level();

	void setSize(unsigned int width, unsigned int height);
	void setSize(Math::Vector2u newSize);
	void setTileSize(float width, float height);
	void setTileSize(Math::Vector2f newSize);
	void setBlock(Math::Vector2u position, int newState);
	bool readLevelFromFile(const std::string &path);
	[[nodiscard]] const std::vector<std::vector<int>> &getLevelData() const;
	Math::Vector2u getSize();
	[[nodiscard]] Math::Vector2<float> castRayFrom(Math::Vector2f position, float angleRadians) const;
	[[nodiscard]] Math::Vector2f getTileSize() const;
};

} // rc

#endif //RAYCASTER_LEVEL_H
