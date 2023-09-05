//
// Created by mateusz on 9/5/23.
//

#ifndef RAYCASTER_SRC_SCENES_LEVEL2D_VIEWAREA_HPP_
#define RAYCASTER_SRC_SCENES_LEVEL2D_VIEWAREA_HPP_

#include "WorldEntity/WorldEntity.hpp"
#include "Math/Math.hpp"
class ViewArea : public WorldEntity {
 public:
	ViewArea();
	void onDraw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void setViewArea(const std::vector<std::pair<Math::Vector2f, float>> &hits, sf::Vector2f playerPos);
 private:
	sf::VertexArray viewArea;
	std::vector<sf::CircleShape> circles;
};

#endif //RAYCASTER_SRC_SCENES_LEVEL2D_VIEWAREA_HPP_
