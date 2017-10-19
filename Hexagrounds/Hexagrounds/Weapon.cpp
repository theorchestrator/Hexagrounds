#include "Weapon.h"

void Weapon::Shoot() {
	std::cout << "Shooting not implemented" << std::endl;
}

int Weapon::GetShootingRange() {
	return shootingRange;
}

int Weapon::GetDamage() {
	return damage;
}

Weapon::WeaponType Weapon::GetWeaponType() {
	return weaponType;
}

void Weapon::SetShootingRange(int shootingRange) {
	this->shootingRange = shootingRange;
}
void Weapon::SetDamage(int damage) {
	this->damage = damage;
}
void Weapon::SetWeaponType(WeaponType weaponType) {
	this->weaponType = weaponType;
}
