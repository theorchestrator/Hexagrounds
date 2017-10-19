#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "TextureManager.h"

TextureManager *TextureManager::instance = 0;

TextureManager* TextureManager::GetInstance() {
	if (!instance) {
		instance = new TextureManager();
	}
	return instance;
}

void TextureManager::preloadTextures() {
	// Floor txtr
	loadTexture("Floor", "Assets\\Textures\\floor.png");
	loadTexture("FloorSelected", "Assets\\Textures\\floorSelected.png");
	loadTexture("FloorAttackable", "Assets\\Textures\\FloorAttackable.png");

	// Player txtr
	loadTexture("Player", "Assets\\Textures\\Player.png");
	loadTexture("PlayerSelected", "Assets\\Textures\\PlayerSelected.png");

	// Txtr
	loadTexture("Empty", "Assets\\Textures\\Empty.png");
	loadTexture("Weapon", "Assets\\Textures\\Weapon.png");
	loadTexture("Enemy", "Assets\\Textures\\Enemy.png");
	//loadTexture("Wall", "Assets\\Textures\\Wall.png");
	loadTexture("Fog", "Assets\\Textures\\Fog.png");
	loadTexture("Grave", "Assets\\Textures\\Grave.png");

	// UI Textr
	loadTexture("Skip", "Assets\\Textures\\Skip.png");
}

void TextureManager::loadTexture(const std::string& name, const std::string& filename)
{
	/* Load the texture */
	sf::Texture tex;
	tex.loadFromFile(filename);

	/* Add it to the list of textures */
	this->textures[name] = tex;

	return;
}

sf::Texture& TextureManager::getRef(const std::string& texture)
{
	return this->textures.at(texture);
}