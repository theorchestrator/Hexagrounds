#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Hexagrid.h"
#include "Player.h"
#include "Enemy.h"
#include "GameUI.h"

class World
{
public:

	enum GameState {PlacementTurn, PlayerTurn, EnemyTurn, PlayerLose, PlayerWin};

	World(sf::RenderWindow& window);
	~World();

	void update(sf::Time dt);
	void draw(sf::RenderWindow &window);
	void SkipPlayerTurn();

private:
	// Input
	bool buttonDown = false;
	bool buttonReleased = true;
	GameState currentGameState;
	GameState oldGameState;
	bool turnUIShown = false;

	bool drawFog = true;

	sf::RenderWindow& windowRef;
	Hexagrid* grid;
	Player* player;
	Enemy* enemy;
	GameUI* gameUI;
	std::vector<sf::RectangleShape> backgroundShapes;
	std::vector<sf::RectangleShape> shapes;
	
	bool CheckIfMouseIsInsideTheWindow(sf::Vector2i mousePos);
	void CheckIfStateChanged();
	void EnemyAction();
	void UserInput();
	void HighlightMouseField();
};

#endif
