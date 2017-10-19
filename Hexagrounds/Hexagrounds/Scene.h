#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <SFML\Graphics.hpp>
#include <map>
#include <iostream>

class Scene {

public:
	virtual void Init(sf::RenderWindow&);
	virtual void Update(sf::Time);
	virtual void Draw(sf::RenderWindow&);
	Scene(){};
};

#endif
