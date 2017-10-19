#include "HealthSystem.h"

// init
HealthSystem::HealthSystem() {
	currentHealth = maxHealth;
}

bool HealthSystem::IsUnitAlive() {
	return isAlive;
}

int HealthSystem::GetCurrentHealth() {
	return currentHealth;
}

void HealthSystem::TakeDamage(int dmgAmount) {
	if (isAlive) {
		currentHealth -= dmgAmount;
		std::cout << "Health = " << currentHealth << std::endl;

		if (currentHealth <= 0) {
			isAlive = false;
			std::cout << "Dead" << std::endl;
		}
	}
}

int HealthSystem::GetMaxHealth() {
	return maxHealth;
}