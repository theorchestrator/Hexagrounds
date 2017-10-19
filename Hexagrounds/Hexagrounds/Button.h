#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "SFML\Graphics.hpp"
#include <iostream>
#include "GUI.h"
#include "Player.h"

class Button : public GUI
{
public:

	Button(int posX, int posY, sf::Texture* texture, Player* player);
	virtual void OnClicked(sf::RenderWindow& window);
	virtual void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);

private:
	bool buttonReleased = true;
	bool buttonDown = false;

	Player* player;

	sf::RectangleShape shape;
};

#endif