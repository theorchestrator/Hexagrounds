#include "GameScene.h"

void GameScene::Init(sf::RenderWindow& window) {
	world = new World(window);
}

void GameScene::Update(sf::Time dt)
{
	//std::cout << "GameScene Update" << std::endl;
	world->update(dt);
}

void GameScene::Draw(sf::RenderWindow &window)
{
	//std::cout << "GameScene Draw" << std::endl;
	world->draw(window);
}
