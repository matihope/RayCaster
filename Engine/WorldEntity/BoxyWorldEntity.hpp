//
// Created by mateusz on 9/6/23.
//

#ifndef RAYCASTER_ENGINE_WORLDENTITY_BOXYWORLDENTITY_HPP_
#define RAYCASTER_ENGINE_WORLDENTITY_BOXYWORLDENTITY_HPP_

#include "WorldEntity.hpp"
#include "Math/Math.hpp"
class BoxyWorldEntity : public WorldEntity {
 public:
	void setMaxRenderSize(Math::Vector2u newSize);
	void setMaxRenderSize(unsigned int width, unsigned int height);
	[[nodiscard]] Math::Vector2u getMaxSize() const;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
 private:
	Math::Vector2u maxSize = {0, 0};
};

#endif //RAYCASTER_ENGINE_WORLDENTITY_BOXYWORLDENTITY_HPP_
