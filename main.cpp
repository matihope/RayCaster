#include "Game/Game.hpp"
#include "Scenes/MenuScene.h"

int main() {
	Game &game = Game::get();
	if (!game.init("settings.json")) return 1;
	game.addScene(std::make_unique<MenuScene>());
	game.run();
}
