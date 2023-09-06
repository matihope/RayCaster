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
}

void Level3D::addRayGame(rc::RayGame *game, Math::Vector2f size) {
	rc_game = game;
	entitySize = size;
	setMaxRenderSize({static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y)});

	floor = addChild<RectShape>(sf::Color(73, 88, 103), sf::Vector2f(size.x, size.y / 2));
	floor->move(0, size.y / 2);
	sky = addChild<RectShape>(sf::Color(135, 206, 235), sf::Vector2f(size.x, size.y / 2));

	verticalBars->setSize(static_cast<std::size_t>(size.x));
	auto [texWidth, texHeight] = verticalBars->getTexture()->getSize();

	for (int x = 0; x < verticalBars->getSize(); x++)
		verticalBars->getSprite(x).setTexSize(sf::Vector2f(1.f, texHeight));
}

void Level3D::setBars(const std::vector<std::pair<Math::Vector2f, float>> &lengths, float fov) {
	auto playerPos = rc_game->getPlayerPosition();
	auto viewHeight = entitySize.y;
	auto fullScreen = rc_game->getLevelTileSize().x / 2.f / std::tan(fov / 2.f) * (entitySize.x / entitySize.y);
	auto [tileWidth, tileHeight] = rc_game->getLevelTileSize();
	auto [texWidth, texHeight] = verticalBars->getTexture()->getSize();

	for (int i = 0; i < lengths.size(); i++) {
		auto rayStop = (lengths[i].first - playerPos).length();
		auto sprite = verticalBars->getSprite(i);
		auto barHeight = viewHeight * fullScreen / (rayStop * std::cos(lengths[i].second - rc_game->getPlayerRotation()));

		sprite.setSize(sf::Vector2f(1.f, barHeight));
		sprite.setPosition(sf::Vector2f(i, (viewHeight - barHeight) / 2));

		float posX = std::fmod(std::roundf(lengths[i].first.x * 1000.f) / 1000.f, tileWidth);
		float posY = std::fmod(std::roundf(lengths[i].first.y * 1000.f) / 1000.f, tileHeight);
		if (Math::isZero(posX)) {
			sprite.setTexPosition({std::round(posY / tileHeight * texWidth), 0.f});
		} else if (Math::isZero(posY)) {
			sprite.setTexPosition({std::round(posX / tileWidth * texWidth), 0.f});
		} else {
			std::cout << lengths[i].first.x << " " << lengths[i].first.y << std::endl;
			std::cout << std::fmod(lengths[i].first.y, tileWidth) << std::endl;
			std::cout << Math::isZero(std::fmod(lengths[i].first.x, tileWidth), 1e-2f) << std::endl;
		}
	}

}
