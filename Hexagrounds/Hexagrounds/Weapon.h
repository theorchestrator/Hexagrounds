#pragma once
#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Weapon
{
public:
	enum WeaponType { MachineGun };

	virtual void Shoot();

	int GetShootingRange();
	int GetDamage();
	WeaponType GetWeaponType();

	void SetShootingRange(int shootingRange);
	void SetDamage(int damage);
	void SetWeaponType(WeaponType weaponType);

private:
	int damage;
	int shootingRange;

	WeaponType weaponType;
};

#endif
