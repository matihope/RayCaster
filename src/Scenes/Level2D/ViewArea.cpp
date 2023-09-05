//
// Created by mateusz on 9/5/23.
//

#include "ViewArea.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Math/Math.hpp"
ViewArea::ViewArea() {
	viewArea.setPrimitiveType(sf::TriangleFan);
}
void ViewArea::onDraw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(viewArea, states);
}
void ViewArea::setViewArea(const std::vector<std::pair<Math::Vector2f, float>> &hits, sf::Vector2f playerPos) {
	viewArea.resize(hits.size() + 1);
	circles.resize(hits.size());
	for (int i = 0; i < hits.size(); i++) {
		viewArea[i + 1].position = {hits[i].first.x, hits[i].first.y};
		viewArea[i + 1].color = sf::Color(189, 213, 234);
	}
	viewArea[0].position = playerPos;
	viewArea[0].color = sf::Color(189, 213, 234);
}
