//
// Created by mateusz on 8/30/23.
//

#ifndef RAYCASTER_ENGINE_NODES_CIRCLESHAPE_HPP_
#define RAYCASTER_ENGINE_NODES_CIRCLESHAPE_HPP_

#include "WorldEntity/WorldEntity.hpp"
class CircleShape : public WorldEntity {
 public:
	CircleShape() = default;
	CircleShape(sf::Color myColor, float radius);
	void onDraw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void setRadius(float radius);
	[[nodiscard]] float getRadius() const;
 private:
	sf::CircleShape circle;
};

#endif //RAYCASTER_ENGINE_NODES_CIRCLESHAPE_HPP_
