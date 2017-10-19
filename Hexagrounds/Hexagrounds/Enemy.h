#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "SFML\Graphics.hpp"
#include "TextureManager.h"
#include "MachineGun.h"
#include "Hexagrid.h"
#include "HealthSystem.h"
#include "EnemyAI.h"
#include "Player.h"
//#include <Windows.h>

class Enemy{
private:
	int posX;
	int posY;
	
	Weapon* currentWeapon;
	HealthSystem* enemyHealth;
	EnemyAI* ai;
	Player* player;
	Hexagrid* grid;

public:

	Enemy();

	// return the array values for his current position
	int GetX();
	int GetY();
	sf::Vector2f GetTilePosition();
	
	void RemoveEnemy();
	void EquipWeapon();
	void MoveToPosition(int mapX, int mapY);
	void SpawnEnemy(Hexagrid* grid, int posX, int posY, Player* player);
	void DamageEnemy(int dmgAmount);
	bool IsAlive();
	void MakeTurn();
};

#endif