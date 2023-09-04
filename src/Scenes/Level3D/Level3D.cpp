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
	floor = addChild<RectShape>(sf::Color(50, 200, 50), sf::Vector2f(view_width / 2, view_height / 2));
	floor->move(0, view_height / 2);
}
void Level3D::addRayGame(rc::RayGame *game) {
	rc_game = game;
	auto [view_width, view_height] = Game::get().getViewportSize();
	view_width /= 2;
	verticalBars->setSize(view_width);

	for (int x = 0; x < verticalBars->getSize(); x++)
		verticalBars->getSprite(x).setTexSize({1.f, 1.f});

}
void Level3D::setBars(std::vector<Math::Vector2f> lengths, float fov) {
	float direction = rc_game->getPlayerRotation() - Math::degreesToRadians(180.f) - fov;
	auto playerPos = rc_game->getPlayerPosition();
	auto [view_width, view_height] = Game::get().getViewportSize();
	auto renderDistance = rc_game->getLevelTileSize().x * 5;

	auto fullScreen = rc_game->getLevelTileSize().x / 2.f / tan(fov / 2.f);
//	auto
	view_width /= 2;
	for (int i = 0; i < lengths.size(); i++) {
		auto rayStop = (lengths[i] - rc_game->getPlayerPosition()).length();
		auto sprite = verticalBars->getSprite(i);
		auto barHeight = view_height * fullScreen / rayStop;
		sprite.setSize(sf::Vector2f(1.f, barHeight));
		sprite.setPosition(sf::Vector2f(i, (view_height - barHeight) / 2));
		sprite.setTexPosition(sf::Vector2f((rayStop / renderDistance) * 128.f, 0));
		direction += fov / 2.f / verticalBars->getSize();
	}

}
