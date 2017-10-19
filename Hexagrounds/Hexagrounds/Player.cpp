#include "Player.h"
#include <functional>

Player::Player() {
	playerHealth = new HealthSystem();
}

void Player::SpawnPlayer(Hexagrid* grid, int posX, int posY) {
	this->grid = grid;
	this->grid->SetTile(posX, posY, Hexagrid::TileType::Player, &TextureManager::GetInstance()->getRef("Player"));
	this->posX = posX;
	this->posY = posY;
	this->grid->CalculateVision(posX, posY, viewRange);
}

void Player::ShowPlayerSelected(bool isSelected) {

	if (isSelected) {
		this->grid->SetTile(posX, posY, Hexagrid::TileType::Player, &TextureManager::GetInstance()->getRef("PlayerSelected"));
		grid->ShowTilesInRange(isSelected, posX, posY, walkRange - movedFields, false);
		
		if (hasWeapon) {
			grid->ShowTilesInRange(isSelected, posX, posY, walkRange, true);
		}
	}
	else {
		this->grid->SetTile(posX, posY, Hexagrid::TileType::Player, &TextureManager::GetInstance()->getRef("Player"));
		grid->ResetSelectedFloor();
		
		if (hasWeapon) {
			grid->ShowTilesInRange(isSelected, posX, posY, walkRange, false);
		}
	}

	// Shows how far the player can walk
	this->isSelected = isSelected;

	//std::cout << "Show Player Selected" << std::endl;
}

bool Player::IsTurnCompleted() {

	bool turnCompleted = false;

	if (movedFields == walkRange && (!hasWeapon || hasWeapon && hasShot) || turnSkipped ) {
		turnCompleted = true;
		//std::cout << "Turn completed" << std::endl;
	}

	// Reset
	if (turnCompleted) {
		movedFields = 0;
		hasShot = false;
		turnSkipped = false;
		//std::cout << "Player Turn Completed" << std::endl;
	}
	
	return turnCompleted;
}

// Needs a parameter for different weapons
void Player::EquipWeapon() {
	if (hasWeapon == false) {
		//std::cout << "Weapon Equiped" << std::endl;
		currentWeapon = new MachineGun();
		hasWeapon = true;
	}
}

void Player::SetSkiptTurn(bool val) {
	turnSkipped = val;
}

bool Player::GetSkiptTurn() {
	return turnSkipped;
}

int Player::GetCurrentWeaponDamage(bool hasShot) {

	int damage = 0;

	if (hasShot && !this->hasShot) {
		this->hasShot = hasShot;
		damage = currentWeapon->GetDamage();
	}

	return damage;
}

void Player::MoveToPosition(int mapX, int mapY, int movementCost) {
	
	if (movedFields + movementCost <= walkRange) {
		//printf("Player Moved");
		movedFields += movementCost;
		this->grid->SetTile(posX, posY, Hexagrid::TileType::Empty, &TextureManager::GetInstance()->getRef("Empty"));

		posX = mapX;
		posY = mapY;

		// Moves the player
		ShowPlayerSelected(false);
	}
}

void Player::RemovePlayer() {
	this->grid->SetTile(posX, posY, Hexagrid::TileType::Empty, &TextureManager::GetInstance()->getRef("Empty"));
}

bool Player::IsWeaponEquiped() {
	return hasWeapon;
}

int Player::GetX() {
	return posX;
}

int Player::GetY() {
	return posY;
}

bool Player::IsPlayerSelected() {
	return isSelected;
}

int Player::GetWalkRange() {
	return walkRange;
}

int Player::GetViewRange() {
	return viewRange;
}

void Player::DamagePlayer(int dmgAmount) {
	this->playerHealth->TakeDamage(dmgAmount);
}
bool Player::IsAlive() {
	return this->playerHealth->IsUnitAlive();
}

// Returns left top corner of the tile. Add 100 / 100 for the full space
sf::Vector2f Player::GetTilePosition() {
	return this->grid->GetTile(posX, posY).bgShape.getPosition();
}


