#include "SceneManager.h"

SceneManager::SceneManager() {
}

void SceneManager::SwitchScene(SceneType sceneType, sf::RenderWindow& window) {
	
	switch (sceneType)
	{
	case SceneType::Game:
		currentScene = new GameScene();
		break;
	case SceneType::MainMenu:
		currentScene = new MainMenuScene();
		break;
	}

	currentScene->Init(window);
}

void SceneManager::Update(sf::Time dt) {
	currentScene->Update(dt);
}

// TODO: SpriteBatch
void SceneManager::Draw(sf::RenderWindow& window) {
	window.clear();
	currentScene->Draw(window);
	window.display();
}