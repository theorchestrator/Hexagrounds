#pragma once
#ifndef GUI_H
#define GUI_H

#include "SFML\Graphics.hpp"
#include <iostream>

class GUI
{
public:
	GUI();
	virtual void OnClicked(sf::RenderWindow& window);
	virtual void Draw(sf::RenderWindow& window);
};

#endif
