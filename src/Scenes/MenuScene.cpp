//
// Created by mateusz on 8/28/23.
//

#include "MenuScene.h"
#include "GUI/Button.hpp"
#include "Game/Game.hpp"
#include "World.h"

MenuScene::MenuScene() {
	m_play_button = addChild<GUI::Button>(Game::get().getFont(), "Start");
	m_play_button->setPosition(int(Game::get().getViewportSize().x / 2),
	                           int(Game::get().getViewportSize().y / 2));
	m_play_button->setTextSize(64);
	m_play_button->setClickMode(Clickable::ClickMode::PressOnRelease);
}

void MenuScene::onUpdate(float dt) {
	if (m_play_button->isPressed()) {
		Game::get().replaceTopScene(std::make_unique<World>());
	}
}
