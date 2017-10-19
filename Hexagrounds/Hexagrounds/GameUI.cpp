#include "GameUI.h"

GameUI::GameUI(Player* player) {
	CreateSkipButton(player);
	InitText();
}

void GameUI::CreateSkipButton(Player* player) {
	skipBtn = new Button(1220, 150, &TextureManager::GetInstance()->getRef("Skip"), player);
}

void GameUI::Draw(sf::RenderWindow& window) {
	skipBtn->Draw(window);
	window.draw(turnText);
}

void GameUI::Update(sf::RenderWindow& window) {
	skipBtn->Update(window);
}

void GameUI::InitText() {

	font.loadFromFile("Assets\\Fonts\\arial.ttf");

	turnText.setFont(font);
	turnText.setFillColor(sf::Color::Blue);
	turnText.setCharacterSize(30);
	turnText.setPosition(1120, 50);
}

void GameUI::SetEnemyText() {
	turnText.setFillColor(sf::Color::Red);
	turnText.setString("ENEMY TURN");
}

void GameUI::SetPlayerText() {
	Sleep(3000);
	turnText.setFillColor(sf::Color::Blue);
	turnText.setString("PLAYER TURN");
}
