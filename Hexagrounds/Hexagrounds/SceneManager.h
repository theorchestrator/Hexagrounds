#pragma once
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include <iostream>

class SceneManager
{
private:
	Scene* currentScene;

public:

	enum SceneType {Game, MainMenu};

	SceneManager();
	void SwitchScene(SceneType, sf::RenderWindow&);
	void Update(sf::Time);
	void Draw(sf::RenderWindow&);
};

#endif