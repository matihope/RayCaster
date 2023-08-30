//
// Created by mateusz on 8/30/23.
//

#ifndef RAYCASTER_ENGINE_NODES_RECTSHAPE_HPP_
#define RAYCASTER_ENGINE_NODES_RECTSHAPE_HPP_

#include "WorldEntity/WorldEntity.hpp"
class RectShape : public WorldEntity {
 public:
	RectShape() = default;
	RectShape(sf::Color myColor, sf::Vector2f size);
	void onDraw(sf::RenderTarget &target, sf::RenderStates states) const override;
 private:
	sf::RectangleShape rect;
};

#endif //RAYCASTER_ENGINE_NODES_RECTSHAPE_HPP_
