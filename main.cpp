#include "Game/Game.hpp"
#include "Scenes/RunScene.h"


int main() {
  Game &game = Game::get();
  if(!game.init("settings.json")) return 1;
  game.addScene(std::make_unique<RunScene>());
  game.run();
}
