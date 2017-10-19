#pragma once
#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "Scene.h"
#include "World.h"

class GameScene : public Scene
{
private:
	World* world;

public:
	virtual void Init(sf::RenderWindow&);
	virtual void Update(sf::Time);
	virtual void Draw(sf::RenderWindow&);
	GameScene(){};
};

#endif

