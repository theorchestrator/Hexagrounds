#include "EnemyAI.h"

EnemyAI::EnemyAI(Hexagrid* grid, Player* player, HealthSystem* enemyHealth) {
	this->grid = grid;
	this->player = player;
	this->enemyHealth = enemyHealth;

	srand(time(NULL));

	int rnd = rand() % 2;

	if(rnd % 2 == 0) 
		currentPlayStyle = PlayStyle::Offensive;
	else 
		currentPlayStyle = PlayStyle::Defensive;

	//std::cout << "Current Playstyle = " << currentPlayStyle << std::endl;
}

EnemyAI::MovementInstructions* EnemyAI::DecideNextMovementAction(int posX, int posY) {

	MovementInstructions* inst = new MovementInstructions();
	currentPosX = posX;
	currentPosY = posY;

	switch (currentPlayStyle)
	{
	case PlayStyle::Offensive:
		inst = OffensiveMovementAction(inst);
		break;
	case PlayStyle::Defensive:
		inst = DefensiveMovementAction(inst);
		break;
	}
	//Sleep(1500);
	//std::cout << "MOVEMENT" << std::endl;
	return inst;
}
EnemyAI::ExecuteInstructions* EnemyAI::DecideNextExecuteAction(int posX, int posY) {

	ExecuteInstructions* inst = new ExecuteInstructions();
	currentPosX = posX;
	currentPosY = posY;

	switch (currentPlayStyle)
	{
	case PlayStyle::Offensive:
		inst = OffensiveExecuteAction(inst);
		break;
	case PlayStyle::Defensive:
		inst = DefensiveExecuteAction(inst);
		break;
	}
	//Sleep(1500);
	//std::cout << "ACTION" << std::endl;
	return inst;
}

// Wander, SeekWeapon, SeekWall, Flee, Wait
EnemyAI::MovementInstructions* EnemyAI::DefensiveMovementAction(MovementInstructions* inst) {
	if (movedFields < walkRange) {
		if (enemyHealth->GetCurrentHealth() <= enemyHealth->GetMaxHealth() / 2) {
			inst = FleeAction(inst);
		}
		else {
			if (turnCount < 2) {
				inst = WanderAction(inst);
			}
			else if (turnCount >= 2 & !hasWeapon && gameHasWeapons) {
				inst = SeekWeaponAction(inst);
			} 
			else if (hasWeapon || !gameHasWeapons) {
				inst = MoveTowardsPlayerAction(inst);
			}
			else {
				inst = WaitAction(inst);
			}
		}
	}
	
	movedFields = 0;
	turnCount++;
	return inst;
}

// Wander, SeekWeapon, MoveTowardsPlayer, Wait
EnemyAI::MovementInstructions* EnemyAI::OffensiveMovementAction(MovementInstructions* inst) {
	if (movedFields < walkRange) {
		if (!hasWeapon && gameHasWeapons) {
			inst = SeekWeaponAction(inst);
		} 
		else {
			if (enemyHealth->GetCurrentHealth() <= enemyHealth->GetMaxHealth() / 2) {
				inst = FleeAction(inst);
			}
			else {
				int rnd = rand() % 3;

				switch (rnd)
				{
				case 0:
					inst = WanderAction(inst);
					break;
				case 1:
					inst = MoveTowardsPlayerAction(inst);
					break;
				case 2:
					inst = WaitAction(inst);
					break;
				}
			}
		}
	}

	movedFields = 0;
	return inst;
}

// Hide, Attack, Idle
EnemyAI::ExecuteInstructions* EnemyAI::DefensiveExecuteAction(ExecuteInstructions* inst) {

	if (!grid->CheckTileInShootingRange(currentPosX, currentPosY, shootingRange) && isNextToWall)
		inst = HideAction(inst);
	else if (grid->CheckTileInShootingRange(currentPosX, currentPosY, shootingRange) && hasWeapon)
		inst = AttackAction(inst);
	else
		inst = IdleAction(inst);

	return inst;
}

// Attack, Idle
EnemyAI::ExecuteInstructions* EnemyAI::OffensiveExecuteAction(ExecuteInstructions* inst) {

	if (grid->CheckTileInShootingRange(currentPosX, currentPosY, shootingRange) && hasWeapon)
		inst = AttackAction(inst);
	else
		inst = IdleAction(inst);

	return inst;
}





/*
MOVEMENT fill instruction
*/

// Active Actions
EnemyAI::MovementInstructions* EnemyAI::WanderAction(MovementInstructions* inst) {
	
	//std::cout << "Wander Action" << std::endl;

	bool newPositionFound = false;
	
	while (!newPositionFound) {
		int rndX = rand() % 2 + 1;
		int rndY = rand() % 2;
		int randomDirection = rand() % 4;

		if (grid->CheckIfTileIsInBounds(currentPosX + rndX, currentPosY + rndY) && grid->CheckIfTileIsAccessable(currentPosX + rndX, currentPosY + rndY) && randomDirection == 0) {
			inst->moveToFieldX = currentPosX + rndX;
			inst->moveToFieldY = currentPosY + rndY;
			newPositionFound = true;
		}
		else if (grid->CheckIfTileIsInBounds(currentPosX - rndX, currentPosY - rndY) && grid->CheckIfTileIsAccessable(currentPosX - rndX, currentPosY - rndY) && randomDirection == 1) {
			inst->moveToFieldX = currentPosX - rndX;
			inst->moveToFieldY = currentPosY - rndY;
			newPositionFound = true;
		}
		else if (grid->CheckIfTileIsInBounds(currentPosX + rndX, currentPosY - rndY) && grid->CheckIfTileIsAccessable(currentPosX + rndX, currentPosY - rndY) && randomDirection == 2) {
			inst->moveToFieldX = currentPosX + rndX;
			inst->moveToFieldY = currentPosY - rndY;
			newPositionFound = true;
		}
		else if (grid->CheckIfTileIsInBounds(currentPosX - rndX, currentPosY + rndY) && grid->CheckIfTileIsAccessable(currentPosX - rndX, currentPosY + rndY) && randomDirection == 3) {
			inst->moveToFieldX = currentPosX - rndX;
			inst->moveToFieldY = currentPosY + rndY;
			newPositionFound = true;
		}
	}
	
	inst->fieldChanged = true;

	return inst;
}

EnemyAI::MovementInstructions* EnemyAI::MoveTowardsPlayerAction(MovementInstructions* inst) {
	//std::cout << "Move Towards Player Action" << std::endl;

	bool newPositionFound = false;

	while (!newPositionFound) {
		int rndX = rand() % 2 + 1;
		int rndY = rand() % 2;

		int xDistance = currentPosX - player->GetX();
		int yDistance = currentPosY - player->GetY();

		// Player is in left direction
		// Going negative left
		if (xDistance > 0)
			rndX = rndX * (-1);

		// Player is in up direction
		// Going negative upwards
		if (yDistance > 0) 
			rndY = rndY * (-1);

		if (grid->CheckIfTileIsInBounds(currentPosX + rndX, currentPosY + rndY) && grid->CheckIfTileIsAccessable(currentPosX + rndX, currentPosY + rndY)) {
			inst->moveToFieldX = currentPosX + rndX;
			inst->moveToFieldY = currentPosY + rndY;
			newPositionFound = true;
		}
	}

	inst->fieldChanged = true;

	return inst;
}

EnemyAI::MovementInstructions* EnemyAI::WaitAction(MovementInstructions* inst) {
	//std::cout << "Wait Action" << std::endl;
	inst->fieldChanged = false;
	return inst;
}

EnemyAI::MovementInstructions* EnemyAI::SeekWeaponAction(MovementInstructions* inst) {
	//std::cout << "Seek Weapon Action" << std::endl;

	bool newPositionFound = false;

	while (!newPositionFound) {
		int rndX = rand() % 2 + 1;
		int rndY = rand() % 2;

		if (grid->GetClosestWeaponTile(currentPosX, currentPosY).type == Hexagrid::TileType::Empty) {
			gameHasWeapons = false;
			break;
		}

		int xDistance = currentPosX - grid->GetClosestWeaponTile(currentPosX, currentPosY).indexX;
		int yDistance = currentPosY - grid->GetClosestWeaponTile(currentPosX, currentPosY).indexY;

		// Player is in left direction
		// Going negative left
		if (xDistance > 0)
			rndX = rndX * (-1);
		else if (xDistance == 0)
			rndX = 0;

		//// Player is in up direction
		//// Going negative upwards
		if (yDistance > 0)
			rndY = rndY * (-1);
		else if (yDistance == 0)
			rndY = 0;


		if (grid->CheckIfTileIsInBounds(currentPosX + rndX, currentPosY + rndY) && grid->CheckIfTileIsAccessable(currentPosX + rndX, currentPosY + rndY)) {
			inst->moveToFieldX = currentPosX + rndX;
			inst->moveToFieldY = currentPosY + rndY;
			newPositionFound = true;
			inst->fieldChanged = true;
			return inst;
		}
	}

	inst->fieldChanged = false;

	return inst;
}

EnemyAI::MovementInstructions* EnemyAI::SeekWallAction(MovementInstructions* inst) {
	//std::cout << "Seek Wall Action" << std::endl;
	inst->fieldChanged = false;
	return inst;
}

// Passive Actions
EnemyAI::MovementInstructions* EnemyAI::FleeAction(MovementInstructions* inst) {
	//std::cout << "Flee Action" << std::endl;

	bool newPositionFound = false;

	while (!newPositionFound) {
		int rndX = rand() % 2 + 1;
		int rndY = rand() % 2;
		int randomUpDown = rand() % 2;
		int xDistance = currentPosX - player->GetX();

		// Player is in Right direction
		// Going negative left
		if (xDistance < 0 && grid->CheckIfTileIsInBounds(currentPosX - rndX, currentPosY + rndY))
			rndX = rndX * (-1);

		// Player is in Down direction
		// Going negative upwards
		if(randomUpDown % 2 == 0 && grid->CheckIfTileIsInBounds(currentPosX + rndX, currentPosY - rndY))
			rndY = rndY * (-1);

		if (grid->CheckIfTileIsInBounds(currentPosX + rndX, currentPosY + rndY) && grid->CheckIfTileIsAccessable(currentPosX + rndX, currentPosY + rndY)) {
			inst->moveToFieldX = currentPosX + rndX;
			inst->moveToFieldY = currentPosY + rndY;
			newPositionFound = true;
		}
		else if(grid->CheckIfTileIsInBounds(currentPosX - rndX, currentPosY + rndY) && grid->CheckIfTileIsAccessable(currentPosX - rndX, currentPosY + rndY)) {
			inst->moveToFieldX = currentPosX - rndX;
			inst->moveToFieldY = currentPosY + rndY;
			newPositionFound = true;
		}
	}

	inst->fieldChanged = true;

	return inst;
}


/*
EXECUTE fill instruction
*/

// Active Actions
EnemyAI::ExecuteInstructions* EnemyAI::AttackAction(ExecuteInstructions* inst) {
	//std::cout << "Attack Action" << std::endl;
	inst->attackPlayer = true;
	inst->hide = false;
	return inst;
}

EnemyAI::ExecuteInstructions* EnemyAI::HideAction(ExecuteInstructions* inst) {
	//std::cout << "Hide Action" << std::endl;
	inst->attackPlayer = false;
	inst->hide = true;
	return inst;
}

EnemyAI::ExecuteInstructions* EnemyAI::IdleAction(ExecuteInstructions* inst) {
	//std::cout << "Idle Action" << std::endl;
	inst->attackPlayer = false;
	inst->hide = false;
	return inst;
}

void EnemyAI::SetHasWeapon(bool val) {
	hasWeapon = val;
}



