#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "SFML\Graphics.hpp"
#include "TextureManager.h"
#include "MachineGun.h"
#include "Hexagrid.h"
#include "HealthSystem.h"

class Player
{
public:

	Player();

	// return the array values for his current position
	int GetX();
	int GetY();
	bool IsPlayerSelected();
	bool IsWeaponEquiped();
	int GetWalkRange();
	int GetViewRange();
	void SetSkiptTurn(bool val);
	bool GetSkiptTurn();
	sf::Vector2f GetTilePosition();
	int GetCurrentWeaponDamage(bool hasShot);

	// Turn based stuff


	void EquipWeapon();
	void MoveToPosition(int mapX, int mapY, int movementCost);
	void SpawnPlayer(Hexagrid* grid, int posX, int posY);
	void ShowPlayerSelected(bool isSelected);
	void RemovePlayer();

	void DamagePlayer(int dmgAmount);
	bool IsAlive();
	bool IsTurnCompleted();

private:
	int posX;
	int posY;
	const int walkRange = 2;
	const int viewRange = 3;

	bool isSelected = false;
	bool hasWeapon = false;

	Weapon* currentWeapon;
	HealthSystem* playerHealth;
	Hexagrid* grid;

	// Turn based variables
	int movedFields = 0;
	bool hasShot = false;
	bool turnSkipped = false;

};

#endif

