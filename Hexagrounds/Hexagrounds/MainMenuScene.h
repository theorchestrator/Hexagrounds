#pragma once
#ifndef MAIN_MENU_SCENE_H
#define MAIN_MENU_SCENE_H

#include "Scene.h"

class MainMenuScene : public Scene
{
private:

public:
	virtual void Init();
	virtual void Update(sf::Time);
	virtual void Draw(sf::RenderWindow&);
	MainMenuScene(){};
};

#endif


