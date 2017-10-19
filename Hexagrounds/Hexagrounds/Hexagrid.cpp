#include <SFML/Graphics.hpp>
#include "Hexagrid.h"
#include <map>

Hexagrid::Hexagrid()
{
	bool hasYOffset = false;

	for (int x = 0; x < tilesX; x++)
	{
		// Check if column has y offset
		if (x % 2 != 0) 
			hasYOffset = true;
		else 
			hasYOffset = false;

		for (int y = 0; y < tilesY; y++)
		{
			CreateTile(x, y, hasYOffset);
		}
	}

	srand(time(NULL));

	int weaponCount = rand() % (4 - 2 + 1) + 2;

	for (int i = 0; i < weaponCount; i++)
	{
		CreateTileAtRandomPos(Hexagrid::TileType::Weapon);
	}
}

void Hexagrid::CreateTileAtRandomPos(Hexagrid::TileType tileType) {

	int rndX = rand() % tilesX;
	int rndY = rand() % tilesY;

	//rndX = 5;
	//rndY = 5;

	sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(100, 100));

	switch (tileType)
	{
	case TileType::Weapon:
		shape.setTexture(&TextureManager::GetInstance()->getRef("Weapon"));
		map[rndX][rndY].type = TileType::Weapon;
		break;
	case TileType::Enemy:
		shape.setTexture(&TextureManager::GetInstance()->getRef("Enemy"));
		map[rndX][rndY].type = TileType::Enemy;
		break;
	case TileType::Wall:
		shape.setTexture(&TextureManager::GetInstance()->getRef("Wall"));
		map[rndX][rndY].type = TileType::Wall;
		break;
	default:
		break;
	}

	map[rndX][rndY].shape = shape;
	map[rndX][rndY].shape.setPosition(sf::Vector2f(map[rndX][rndY].posX, map[rndX][rndY].posY));
	map[rndX][rndY].isValid = true;
}

void Hexagrid::CreateTile(int indexX, int indexY, bool hasYOffset) 
{
	sf::RectangleShape backgroundShape = sf::RectangleShape(sf::Vector2f(100, 100));
	backgroundShape.setTexture(&TextureManager::GetInstance()->getRef("Floor"));

	sf::RectangleShape fogShape = sf::RectangleShape(sf::Vector2f(100, 100));
	fogShape.setTexture(&TextureManager::GetInstance()->getRef("Fog"));
	
	float calculatedXpos;
	float calculatedYpos;

	if (hasYOffset) 
	{
		calculatedXpos = indexX * backgroundShape.getSize().x - indexX * (backgroundShape.getSize().x / 4);
		calculatedYpos = indexY * backgroundShape.getSize().y + backgroundShape.getSize().y / 2;
	}
	else 
	{
		if (indexX == 0) 
		{
			calculatedXpos = indexX * backgroundShape.getSize().x;
			calculatedYpos = indexY * backgroundShape.getSize().y;
		}
		else
		{
			calculatedXpos = indexX * backgroundShape.getSize().x - indexX * (backgroundShape.getSize().x / 4);
			calculatedYpos = indexY * backgroundShape.getSize().y;
		}
	}

	backgroundShape.setPosition(sf::Vector2f(calculatedXpos, calculatedYpos));
	fogShape.setPosition(sf::Vector2f(calculatedXpos, calculatedYpos));

	// Init Tile
	Tile tile;
	tile.posX = (int)calculatedXpos;
	tile.posY = (int)calculatedYpos;
	tile.indexX = indexX;
	tile.indexY = indexY;
	tile.canBeClicked = false;
	tile.isValid = true;
	tile.movementCost = 0;

	// half of the background tile shape
	sf::Vector2f centerOffset(50, 50); 

	// getPosition() + centerOffset (50px) on x & y returns the center of each tile (since the rectangle shape is 100px)
	tile.center = backgroundShape.getPosition() + centerOffset;
	tile.bgShape = backgroundShape;
	tile.fogShape = fogShape;
	tile.type = TileType::Empty;

	map[indexX][indexY] = tile;
}

// returns a copy
Hexagrid::Tile Hexagrid::GetTileRelativeToMouse(sf::Vector2i mousePos) {
	for (int x = 0; x < tilesX; x++)
	{
		for (int y = 0; y < tilesY; y++)
		{
			if ((mousePos.x < map[x][y].bgShape.getPosition().x + 101 && mousePos.x > map[x][y].bgShape.getPosition().x - 1) &&
				(mousePos.y < map[x][y].bgShape.getPosition().y + 101 && mousePos.y > map[x][y].bgShape.getPosition().y - 1)) {
				return map[x][y];
				break;
			}
		}
	}

	std::cout << "No Tile found" << std::endl;
}

void Hexagrid::HighlightMousePos(sf::Vector2i mousePos) {

	sf::RectangleShape rs = sf::RectangleShape(sf::Vector2f(100, 100));
	rs.setTexture(&TextureManager::GetInstance()->getRef("FloorSelected"));

	for (int x = 0; x < tilesX; x++)
	{
		for (int y = 0; y < tilesY; y++)
		{
			if ((mousePos.x < map[x][y].fogShape.getPosition().x + 101 && mousePos.x > map[x][y].fogShape.getPosition().x - 1) &&
				(mousePos.y < map[x][y].fogShape.getPosition().y + 101 && mousePos.y > map[x][y].fogShape.getPosition().y - 1)) {
				map[x][y].fogShape = rs;
				map[x][y].fogShape.setPosition(map[x][y].posX, map[x][y].posY);
				map[x][y].canBeClicked = true;
				break;
			}
		}
	}
}

// returns a copy
Hexagrid::Tile Hexagrid::GetTile(int x, int y) {
	return map[x][y];
}

bool Hexagrid::CheckIfTileIsInBounds(int posX, int posY) {
	if ((posX >= 0 && posX <= tilesX - 1) && (posY >= 0 && posY <= tilesY - 1))
		return true;
	else
		return false;
}

void Hexagrid::SetTile(int x, int y, TileType type, sf::Texture* texture) {
	sf::RectangleShape rs = sf::RectangleShape(sf::Vector2f(100, 100));
	rs.setTexture(texture);

	map[x][y].shape = rs;
	map[x][y].shape.setPosition(map[x][y].posX, map[x][y].posY);
	map[x][y].type = type;
}

void Hexagrid::DrawBackgroundShapes(sf::RenderWindow& window) {
	for (int x = 0; x < tilesX; x++)
	{
		for (int y = 0; y < tilesY; y++)
		{
			window.draw(map[x][y].bgShape);
		}
	}
}

void Hexagrid::DrawShapes(sf::RenderWindow& window) {
	for (int x = 0; x < tilesX; x++)
	{
		for (int y = 0; y < tilesY; y++)
		{
			window.draw(map[x][y].shape);
		}
	}
}

void Hexagrid::DrawFogShapes(sf::RenderWindow& window) {
	for (int x = 0; x < tilesX; x++)
	{
		for (int y = 0; y < tilesY; y++)
		{
			window.draw(map[x][y].fogShape);
		}
	}
}

Hexagrid::Tile Hexagrid::GetClosestWeaponTile(int posX, int posY) {

	Tile closestWeaponTile;
	int closestDistanceX = 100;
	int distanceX = 0;
	bool foundTile = false;

	for (int x = 0; x < tilesX; x++)
	{
		for (int y = 0; y < tilesY; y++)
		{
			if (map[x][y].type == TileType::Weapon) {
				distanceX = abs(posX - x);

				if (closestDistanceX > distanceX) {
					closestDistanceX = distanceX;
					closestWeaponTile = map[x][y];
					foundTile = true;
				}
			}
		}
	}

	if (!foundTile)
		closestWeaponTile = GetRandomTileByType(TileType::Empty);


	return closestWeaponTile;
}

// Shooting Range for Player with visualization
void Hexagrid::ShowTilesInRange(bool showTiles, int posX, int posY, int walkRange, bool checkShootingRange) {
	sf::RectangleShape rs = sf::RectangleShape(sf::Vector2f(100, 100));

	if (checkShootingRange) {
		walkRange += 1;
	}
	
	if (showTiles) {
		if(checkShootingRange)
			rs.setTexture(&TextureManager::GetInstance()->getRef("FloorAttackable"));
		else
			rs.setTexture(&TextureManager::GetInstance()->getRef("FloorSelected"));
		

		for (int x = -walkRange; x <= walkRange; x++)
		{
			for (int y = -walkRange; y <= walkRange; y++)
			{
				//std::cout << y << std::endl;
				if (CheckIfTileIsInBounds(posX - x, posY - y)) {
					if (CheckIfTileIsValid(posX, x, y, walkRange) && (map[posX - x][posY - y].type != TileType::Wall)) {
						if ((!checkShootingRange &&  map[posX - x][posY - y].type != TileType::Enemy) || (checkShootingRange && CheckIfTileIsValid(posX, x, y, walkRange + 1) && map[posX - x][posY - y].type == TileType::Enemy)) {
							map[posX - x][posY - y].bgShape = rs;
							map[posX - x][posY - y].bgShape.setPosition(map[posX - x][posY - y].posX, map[posX - x][posY - y].posY);
							map[posX - x][posY - y].canBeClicked = true;
							map[posX - x][posY - y].movementCost = CalculateMovementCost(x, y, walkRange);
						}
					}
				}
			}
		}
	}
	else {
		rs.setTexture(&TextureManager::GetInstance()->getRef("Floor"));

		for (int x = -walkRange; x <= walkRange; x++)
		{
			for (int y = -walkRange; y <= walkRange; y++)
			{
				if (CheckIfTileIsInBounds(posX - x, posY - y)) {
					map[posX - x][posY - y].bgShape = rs;
					map[posX - x][posY - y].bgShape.setPosition(map[posX - x][posY - y].posX, map[posX - x][posY - y].posY);
					map[posX - x][posY - y].canBeClicked = false;
					map[posX - x][posY - y].movementCost = 0;
				}
			}
		}
	}
}

// Shooting range for Enemy without visualization
bool Hexagrid::CheckTileInShootingRange(int posX, int posY, int range) {

	for (int x = -range; x <= range; x++)
	{
		for (int y = -range; y <= range; y++)
		{
			if (CheckIfTileIsInBounds(posX - x, posY - y)) {
				if ((CheckIfTileIsValid(posX, x, y, range) && (map[posX - x][posY - y].type != TileType::Wall)) && (map[posX - x][posY - y].type == TileType::Player)) {
					return true;
				}
			}
		}
	}

	return false;
}

int Hexagrid::CalculateMovementCost(int walkX, int walkY, int walkRange) {
	if (walkRange > 1) {
		if (walkX == walkRange || walkY == walkRange || -walkX == walkRange || -walkY == walkRange)
			return maxMovementCost;
		else
			return minMovementCost;
	}
	else {
		return minMovementCost;
	}
	
}

Hexagrid::Tile Hexagrid::GetRandomTileByType(Hexagrid::TileType tileType) {

	int rndThreshold = rand() % 60 + 10;
	int counter = 0;

	for (int x = 0; x < tilesX; x++) 
	{
		for (int y = 0; y < tilesY; y++) 
		{
			if (map[x][y].type == tileType) {
				counter++;
				if (counter == rndThreshold) {
					return map[x][y];
				}
			}
		}
	}
}

void Hexagrid::ResetSelectedFloor() {
	sf::RectangleShape rs = sf::RectangleShape(sf::Vector2f(100, 100));
	rs.setTexture(&TextureManager::GetInstance()->getRef("Floor"));

	for (int x = 0; x < tilesX; x++)
	{
		for (int y = 0; y < tilesY; y++)
		{
			map[x][y].bgShape = rs;
			map[x][y].bgShape.setPosition(map[x][y].posX, map[x][y].posY);
			map[x][y].canBeClicked = false;
			map[x][y].movementCost = 0;
		}
	}
}

void Hexagrid::ResetFog() {
	sf::RectangleShape rs = sf::RectangleShape(sf::Vector2f(100, 100));
	rs.setTexture(&TextureManager::GetInstance()->getRef("Fog"));

	for (int x = 0; x < tilesX; x++)
	{
		for (int y = 0; y < tilesY; y++)
		{
			map[x][y].fogShape = rs;
			map[x][y].fogShape.setPosition(map[x][y].posX, map[x][y].posY);
		}
	}
}

void Hexagrid::CalculateVision(int posX, int posY, int viewRange) {
	sf::RectangleShape rs = sf::RectangleShape(sf::Vector2f(100, 100));
	rs.setTexture(&TextureManager::GetInstance()->getRef("Empty"));

	for (int x = -viewRange; x <= viewRange; x++)
	{
		for (int y = -viewRange; y <= viewRange; y++)
		{
			//std::cout << y << std::endl;
			if (CheckIfTileIsInBounds(posX - x, posY - y)) {
				if (CheckIfTileIsValid(posX, x, y, viewRange)) {
					map[posX - x][posY - y].fogShape = rs;
					map[posX - x][posY - y].fogShape.setPosition(map[posX - x][posY - y].posX, map[posX - x][posY - y].posY);
				}
			}
		}
	}

}

// Holy shit
bool Hexagrid::CheckIfTileIsValid(int posX, int xMovement, int yMovement, int walkRange) {

	bool tileIsValid = true;
	// Calculating with max range
	int yTilePosMax = 0;
	// Calculating with min range
	int yTilePosMin = 0;

	bool isEven = true;


	// Handling 2 or less tiles range
	if (walkRange <= maxWalkRange) {
		if (posX % 2 == 0) {
			yTilePosMax = -4;
			yTilePosMin = -2;
		}

		//Corners are Invalid
		// Movement for max Walk range and Shooting range
		if (walkRange == maxWalkRange) {
			if ((xMovement - walkRange == 0 && yMovement - walkRange == 0) ||
				(xMovement + walkRange == 0 && yMovement + walkRange == 0) ||
				(xMovement - walkRange == 0 && yMovement + walkRange == 0) ||
				(xMovement + walkRange == 0 && yMovement - walkRange == 0)) {

				tileIsValid = false;
			}

			//Check next to the top corners. These are unreachable because of the tile layout we selected
			if ((xMovement - walkRange == -1 && yMovement - walkRange == yTilePosMax) ||
				(xMovement + walkRange == 1 && yMovement - walkRange == yTilePosMax)) {
				tileIsValid = false;
			}
		}
		else {
			if ((xMovement - walkRange == -2 && yMovement - walkRange == yTilePosMin) ||
				(xMovement + walkRange == 2 && yMovement - walkRange == yTilePosMin)) {
				tileIsValid = false;
			}
		}

	}
	// Handling 3 tiles range
	else {
		// Determines if next field is even or odd
		if (posX % 2 == 0) {
			isEven = false;
			//std::cout << isEven << std::endl;
		}

		// Corners
		if ((xMovement - walkRange == 0 && yMovement - walkRange == 0) ||
			(xMovement + walkRange == 0 && yMovement + walkRange == 0) ||
			(xMovement - walkRange == 0 && yMovement + walkRange == 0) ||
			(xMovement + walkRange == 0 && yMovement - walkRange == 0)) {

			tileIsValid = false;
		}

		// Handling top tiles
		if ((xMovement - walkRange == -1 && yMovement - walkRange == 0) ||
			(xMovement + walkRange == 1 && yMovement - walkRange == 0)) {

			tileIsValid = false;
		}

		if (isEven) {
			if ((xMovement - walkRange == -2 && yMovement - walkRange == 0) ||
				(xMovement + walkRange == 2 && yMovement - walkRange == 0) ||
				(xMovement - walkRange == 0 && yMovement - walkRange == -1) ||
				(xMovement + walkRange == 0 && yMovement - walkRange == -1)) {
				tileIsValid = false;
			}
		}

		// Handling bottom tiles
		if ((xMovement - walkRange == -1 && yMovement + walkRange == 0) ||
			(xMovement + walkRange == 1 && yMovement + walkRange == 0)) {

			tileIsValid = false;
		}

		if (!isEven) {
			if ((xMovement - walkRange == -2 && yMovement + walkRange == 0) ||
				(xMovement + walkRange == 2 && yMovement + walkRange == 0) ||
				(xMovement - walkRange == 0 && yMovement + walkRange == 1) ||
				(xMovement + walkRange == 0 && yMovement + walkRange == 1)) {
				tileIsValid = false;
			}
		}
	}

	return tileIsValid;
}

// Needed for Enemy AI;
bool Hexagrid::CheckIfTileIsAccessable(int posX, int posY) {
	if (map[posX][posY].type != TileType::Wall && map[posX][posY].type != TileType::Player)
		return true;
	else
		return false;
}

Hexagrid::~Hexagrid() {}
