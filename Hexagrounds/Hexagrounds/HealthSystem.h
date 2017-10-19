#pragma once
#ifndef HEALTH_SYSTEM_H
#define HEALTH_SYSTEM_H

#include "SFML\Graphics.hpp"
#include <iostream>

class HealthSystem
{
public:
	HealthSystem();

	int GetCurrentHealth();
	void TakeDamage(int dmgAmount);
	bool IsUnitAlive();
	int GetMaxHealth();

private:

	bool isAlive = true;
	int currentHealth;
	int maxHealth = 4;
};

#endif
