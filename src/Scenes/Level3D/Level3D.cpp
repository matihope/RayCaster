//
// Created by mateusz on 8/31/23.
//

#include "Level3D.hpp"
#include "Game/Game.hpp"
#include "ResourceManager/ResourceManager.hpp"

Level3D::Level3D() {
	rc_game = nullptr;
	verticalBars = addChild<SpriteBatch, 1>();
	verticalBars->setTexture(&ResourceManager::get().getTexture("resources/Castle_Wall.png"));

	auto [view_width, view_height] = Game::get().getViewportSize();
	floor = addChild<RectShape>(sf::Color(73, 88, 103), sf::Vector2f(view_width / 2, view_height / 2));
	floor->move(0, view_height / 2);
}

void Level3D::addRayGame(rc::RayGame *game) {
	rc_game = game;
	auto [view_width, view_height] = Game::get().getViewportSize();
	view_width /= 2;
	verticalBars->setSize(view_width);
	auto [texWidth, texHeight] = verticalBars->getTexture()->getSize();

	for (int x = 0; x < verticalBars->getSize(); x++)
		verticalBars->getSprite(x).setTexSize(sf::Vector2f(1.f, texHeight));
}

void Level3D::setBars(const std::vector<std::pair<Math::Vector2f, float>> &lengths, float fov) {
	auto playerPos = rc_game->getPlayerPosition();
	auto viewHeight = Game::get().getViewportSize().y;
	auto fullScreen = rc_game->getLevelTileSize().x / 2.f / std::tan(fov / 2.f);
	auto [tileWidth, tileHeight] = rc_game->getLevelTileSize();
	auto [texWidth, texHeight] = verticalBars->getTexture()->getSize();

	for (int i = 0; i < lengths.size(); i++) {
		auto rayStop = (lengths[i].first - playerPos).length();
		auto sprite = verticalBars->getSprite(i);
		auto barHeight = viewHeight * fullScreen / (rayStop * std::cos(lengths[i].second - rc_game->getPlayerRotation()));

		sprite.setSize(sf::Vector2f(1.f, barHeight));
		sprite.setPosition(sf::Vector2f(i, (viewHeight - barHeight) / 2));
		if (Math::isZero(std::fmod(std::roundf(lengths[i].first.x * 1000.f) / 1000.f, tileWidth))) {
			sprite.setTexPosition({std::round(std::fmod(lengths[i].first.y, tileWidth) / tileWidth * texWidth), 0.f});
		} else if (Math::isZero(std::fmod(std::roundf(lengths[i].first.y * 1000.f) / 1000.f, tileWidth))) {
			sprite.setTexPosition({std::round(std::fmod(lengths[i].first.x, tileWidth) / tileWidth * texWidth), 0.f});
		} else {
			std::cout << lengths[i].first.x << " " << lengths[i].first.y << std::endl;
			std::cout << std::fmod(lengths[i].first.y, tileWidth) << std::endl;
			std::cout << Math::isZero(std::fmod(lengths[i].first.x, tileWidth), 1e-2f) << std::endl;
		}
	}

}
