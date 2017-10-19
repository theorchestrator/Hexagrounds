#include "Enemy.h"


Enemy::Enemy() {
	enemyHealth = new HealthSystem();
}

void Enemy::SpawnEnemy(Hexagrid* grid, int posX, int posY, Player* player) {
	this->grid = grid;
	this->grid->SetTile(posX, posY, Hexagrid::TileType::Enemy, &TextureManager::GetInstance()->getRef("Enemy"));
	this->posX = posX;
	this->posY = posY;
	this->player = player;

	ai = new EnemyAI(grid, player, enemyHealth);
}

// Needs a parameter for different weapons
void Enemy::EquipWeapon() {
	std::cout << "Enemy Weapon Equiped" << std::endl;
	currentWeapon = new MachineGun();
	ai->SetHasWeapon(true);
}

void Enemy::MoveToPosition(int mapX, int mapY) {
	this->grid->SetTile(posX, posY, Hexagrid::TileType::Empty, &TextureManager::GetInstance()->getRef("Empty"));

	posX = mapX;
	posY = mapY;

	if (grid->GetTile(posX, posY).type == Hexagrid::TileType::Weapon) {
		EquipWeapon();
	}

	this->grid->SetTile(posX, posY, Hexagrid::TileType::Enemy, &TextureManager::GetInstance()->getRef("Enemy"));
}

void Enemy::MakeTurn() {

	EnemyAI::MovementInstructions* movementInst;
	movementInst = ai->DecideNextMovementAction(posX, posY);

	if (movementInst->fieldChanged) {
		MoveToPosition(movementInst->moveToFieldX, movementInst->moveToFieldY);
	}

	//Sleep(1500);
	
	// DO MOVEMENT ACTIONS AND CALL EXECUTE WITH NEW POS
	EnemyAI::ExecuteInstructions* executeInst;
	executeInst = ai->DecideNextExecuteAction(posX, posY);

	if (executeInst->attackPlayer) {
		player->DamagePlayer(currentWeapon->GetDamage());
	}
}

void Enemy::DamageEnemy(int dmgAmount) {
	this->enemyHealth->TakeDamage(dmgAmount);
}

bool Enemy::IsAlive() {
	return this->enemyHealth->IsUnitAlive();
}

void Enemy::RemoveEnemy() {
	this->grid->SetTile(posX, posY, Hexagrid::TileType::Empty, &TextureManager::GetInstance()->getRef("Empty"));
}

int Enemy::GetX() {
	return posX;
}

int Enemy::GetY() {
	return posY;
}

// Returns left top corner of the tile. Add 100 / 100 for the full space
sf::Vector2f Enemy::GetTilePosition() {
	return this->grid->GetTile(posX, posY).bgShape.getPosition();
}