#pragma once
#ifndef HEXAGRID_H
#define HEXAGRID_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "TextureManager.h"

class Hexagrid
{

public:
	enum TileType {Empty, Player, Enemy, Weapon, Wall};

	struct Tile
	{

	public:
		int posX;
		int posY;
		int indexX;
		int indexY;
		sf::Vector2f center;
		sf::RectangleShape bgShape;
		sf::RectangleShape shape;
		sf::RectangleShape fogShape;
		TileType type;
		bool canBeClicked;
		int movementCost;
		bool isValid = false;
	};

	Hexagrid();
	~Hexagrid();

	Tile GetTile(int x, int y);
	Tile GetClosestWeaponTile(int posX, int posY);
	Tile Hexagrid::GetTileRelativeToMouse(sf::Vector2i mousePos);
	bool CheckIfTileIsInBounds(int posX, int posY);
	bool CheckIfTileIsAccessable(int posX, int posY);
	bool CheckTileInShootingRange(int posX, int posY, int range);
	void ResetSelectedFloor();
	void ResetFog();
	void CalculateVision(int posX, int posY, int viewRange);

	void SetTile(int x, int y, TileType type, sf::Texture* shapedTexture);
	void ShowTilesInRange(bool showTiles, int posX, int posY, int walkRange, bool checkShootingRange);
	void DrawBackgroundShapes(sf::RenderWindow& window);
	void DrawShapes(sf::RenderWindow& window);
	void DrawFogShapes(sf::RenderWindow& window);
	void HighlightMousePos(sf::Vector2i mousePos);
	Tile GetRandomTileByType(TileType tileType);

private:

	const int maxMovementCost = 2;
	const int minMovementCost = 1;
	const int maxWalkRange = 2;

	static const int tilesX = 16;
	static const int tilesY = 7;

	Tile map[tilesX][tilesY];
	
	void CreateTile(int posX, int posY, bool hasYOffset);
	void CreateTileAtRandomPos(TileType tileType);
	bool CheckIfTileIsValid(int posX, int xMovement, int yMovement, int walkRange);
	int CalculateMovementCost(int walkX, int walkY, int walkRange);
};

#endif


