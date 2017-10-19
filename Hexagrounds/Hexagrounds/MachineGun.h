#pragma once
#ifndef MACHINE_GUN_HPP
#define MACHINE_GUN_HPP

#include <SFML/Graphics.hpp>
#include "Weapon.h"

class MachineGun : public Weapon
{
public:
	MachineGun();

	virtual void Shoot();
private:
	// Weapon props
	int shootingRange = 3;
	int damage = 2;

};

#endif