#include <SFML/Graphics.hpp>
#include "Hexagrid.h"
#include "SceneManager.h"
#include "TextureManager.h"
#include <thread>
#include <chrono>

using namespace sf;

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

int main()
{
	RenderWindow window(VideoMode(1360, 768), "Hexagrounds");

	// Preload all textures lel
	TextureManager::GetInstance()->preloadTextures();
	
	SceneManager* sceneManager = new SceneManager();
	sceneManager->SwitchScene(SceneManager::SceneType::Game, window);
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		sceneManager->Update(TimePerFrame);
		sceneManager->Draw(window);
	}

	return 0;
}
