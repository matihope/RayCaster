//
// Created by mateusz on 8/31/23.
//

#include "Level3D.hpp"
#include "Game/Game.hpp"
#include "ResourceManager/ResourceManager.hpp"

Level3D::Level3D() {
	rc_game = nullptr;
	verticalBars = addChild<SpriteBatch, 1>();
	verticalBars->setTexture(&ResourceManager::get().getTexture("resources/walls.png"));

	auto [view_width, view_height] = Game::get().getViewportSize();
	floor = addChild<RectShape>(sf::Color(73, 88, 103), sf::Vector2f(view_width / 2, view_height / 2));
	floor->move(0, view_height / 2);
}

void Level3D::addRayGame(rc::RayGame *game) {
	rc_game = game;
	auto [view_width, view_height] = Game::get().getViewportSize();
	view_width /= 2;
	verticalBars->setSize(view_width);

	for (int x = 0; x < verticalBars->getSize(); x++)
		verticalBars->getSprite(x).setTexSize({1.f, 256.f});
}

void Level3D::setBars(const std::vector<std::pair<Math::Vector2f, float>> &lengths, float fov) {
	auto playerPos = rc_game->getPlayerPosition();
	auto view_height = Game::get().getViewportSize().y;
	auto renderDistance = rc_game->getLevelTileSize().x * 5;
	auto fullScreen = rc_game->getLevelTileSize().x / 2.f / std::tan(fov / 2.f);

	for (int i = 0; i < lengths.size(); i++) {
		auto rayStop = (lengths[i].first - playerPos).length();
		auto sprite = verticalBars->getSprite(i);
		auto barHeight = view_height * fullScreen / (rayStop * std::cos(lengths[i].second - rc_game->getPlayerRotation()));

		sprite.setSize(sf::Vector2f(1.f, barHeight));
		sprite.setPosition(sf::Vector2f(i, (view_height - barHeight) / 2));
		sprite.setTexPosition(sf::Vector2f((rayStop / renderDistance) * 256.f, 0));
	}

}
