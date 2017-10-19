#pragma once
#ifndef GAME_UI_H
#define GAME_UI_H

#include "SFML\Graphics.hpp"
#include <iostream>
#include "Button.h"
#include "TextureManager.h"
#include "Player.h"
#include <Windows.h>

class GameUI
{
public:
	GameUI(Player* player);
	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);


	void SetPlayerText();
	void SetEnemyText();

private:
	void CreateSkipButton(Player* player);
	void InitText();

	Button* skipBtn;
	sf::Font font;
	sf::Text turnText;
};

#endif