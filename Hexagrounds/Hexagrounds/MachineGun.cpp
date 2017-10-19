#include "MachineGun.h"

MachineGun::MachineGun() {
	this->SetShootingRange(shootingRange);
	this->SetDamage(damage);
	this->SetWeaponType(Weapon::WeaponType::MachineGun);
}

void MachineGun::Shoot() {
	// Shoot stuff
	std::cout << "PENG" << std::endl;
}