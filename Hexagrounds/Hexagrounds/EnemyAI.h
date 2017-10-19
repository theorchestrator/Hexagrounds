#pragma once
#ifndef ENEMY_AI_H
#define ENEMY_AI_H

#include "SFML\Graphics.hpp"
#include <iostream>
#include "Hexagrid.h"
// Needed to for Movement calculations
#include "Player.h"
#include "HealthSystem.h"
#include <Windows.h>

class EnemyAI
{
public:
	enum PlayStyle { Defensive, Offensive};

	struct MovementInstructions
	{
	public:
		int moveToFieldX;
		int moveToFieldY;
		bool fieldChanged;
	};

	struct ExecuteInstructions
	{
	public:
		bool attackPlayer;
		bool hide;
	};

	EnemyAI(Hexagrid* grid, Player* player, HealthSystem* enemyHealth);

	MovementInstructions* DecideNextMovementAction(int posX, int posY);
	ExecuteInstructions* DecideNextExecuteAction(int posX, int posY);
	void SetHasWeapon(bool val);

private:
	Hexagrid* grid;
	PlayStyle currentPlayStyle;
	Player* player;
	HealthSystem* enemyHealth;

	int currentPosX;
	int currentPosY;

	int walkRange = 2;
	int shootingRange = 3;
	int movedFields = 0;
	int turnCount = 0;
	bool hasWeapon = false;
	bool gameHasWeapons = true;
	//bool isHiding = false;
	bool isNextToWall = false;

	MovementInstructions* DefensiveMovementAction(MovementInstructions* inst);
	MovementInstructions* OffensiveMovementAction(MovementInstructions* inst);

	ExecuteInstructions* DefensiveExecuteAction(ExecuteInstructions* inst);
	ExecuteInstructions* OffensiveExecuteAction(ExecuteInstructions* inst);

	/**
	AI is Action baed and has different Actions to choose from. Actions are limited by the play styles of the AI
	- e.g a deffensive play style does not involve aggressive movements towards the player
	- e.g. a offensive play style does not involve hiding behind a wall or fleeing
	*/
	MovementInstructions* WanderAction(MovementInstructions* inst);
	MovementInstructions* MoveTowardsPlayerAction(MovementInstructions* inst);
	MovementInstructions* SeekWallAction(MovementInstructions* inst);
	MovementInstructions* SeekWeaponAction(MovementInstructions* inst);
	MovementInstructions* FleeAction(MovementInstructions* inst);
	MovementInstructions* WaitAction(MovementInstructions* inst);

	ExecuteInstructions* AttackAction(ExecuteInstructions* inst);
	ExecuteInstructions* HideAction(ExecuteInstructions* inst);
	ExecuteInstructions* IdleAction(ExecuteInstructions* inst);
};

#endif
