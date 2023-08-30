//
// Created by mateusz on 8/28/23.
//

#ifndef RAYCASTER_RUNSCENE_H
#define RAYCASTER_RUNSCENE_H

#include "WorldEntity/WorldEntity.hpp"
#include "GUI/Button.hpp"

class MenuScene : public WorldEntity {
 public:
	MenuScene();
	void onUpdate(float dt) override;
 private:
	GUI::Button *m_play_button;
};

#endif //RAYCASTER_RUNSCENE_H
