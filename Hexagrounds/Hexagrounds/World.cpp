#include "World.h"
#include <iostream>

World::World(sf::RenderWindow& window) : windowRef(window)
{
	grid = new Hexagrid();
	player = new Player();
	enemy = new Enemy();
	currentGameState = GameState::PlacementTurn;
	oldGameState = currentGameState;
	gameUI = new GameUI(player);
}

World::~World()
{
}

void World::update(sf::Time dt) {

	CheckIfStateChanged();

	switch (currentGameState)
	{
		case GameState::EnemyTurn:
			if (!turnUIShown) {
				turnUIShown = true;
				gameUI->SetEnemyText();
			}
			//std::cout << "Enemy Action" << std::endl;
			EnemyAction();
			currentGameState = GameState::PlayerTurn;
			break;
		case GameState::PlayerTurn:
			if (!turnUIShown) {
				turnUIShown = true;
				gameUI->SetPlayerText();
			}
			UserInput();
			if (player->IsTurnCompleted()) {
				currentGameState = GameState::EnemyTurn;
			}
			break;
		case GameState::PlacementTurn: 
			grid->ResetFog();
			HighlightMouseField();
			break;
		case GameState::PlayerWin:
			enemy->RemoveEnemy();
			grid->ResetSelectedFloor();
			break;
		case GameState::PlayerLose:
			player->RemovePlayer();
			break;
	}

	if (!enemy->IsAlive())
		currentGameState = GameState::PlayerWin;
	else if (!player->IsAlive())
		currentGameState = GameState::PlayerLose;

	// who cares about dt
	gameUI->Update(windowRef);
}

void World::EnemyAction() {
	enemy->MakeTurn();
}

void World::SkipPlayerTurn() {
	currentGameState = GameState::EnemyTurn;
}

void World::CheckIfStateChanged() {
	if (currentGameState != oldGameState) {
		turnUIShown = false;
		oldGameState = currentGameState;
	}
}

void World::UserInput() {
 
	// Used for Debugging the Enemy Turns
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
		currentGameState = GameState::EnemyTurn;
	}

	// toggle fog
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
		drawFog = !drawFog;
	}

	sf::Vector2i mousePos = sf::Mouse::getPosition(windowRef);

	if (CheckIfMouseIsInsideTheWindow(mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && buttonReleased == true) {
			// Select Player if you click in the Player Rect
			if (player->IsPlayerSelected() == false &&
				(mousePos.x < player->GetTilePosition().x + 101 && mousePos.x > player->GetTilePosition().x - 1) &&
				(mousePos.y < player->GetTilePosition().y + 101 && mousePos.y > player->GetTilePosition().y - 1)) {
				player->ShowPlayerSelected(true);
			}
			// if player is selected check if the click is in a click able tile -> follow action
			else if (player->IsPlayerSelected()) {
				if (mousePos.x < windowRef.getSize().x - 120) {
					Hexagrid::Tile tile = grid->GetTileRelativeToMouse(sf::Mouse::getPosition(windowRef));

					if (tile.isValid) {
						if (tile.canBeClicked == true) {
							switch (tile.type)
							{
							case Hexagrid::TileType::Empty:

								player->MoveToPosition(tile.indexX, tile.indexY, tile.movementCost);
								// Reset and load new;
								grid->ResetFog();
								grid->CalculateVision(tile.indexX, tile.indexY, player->GetViewRange());
								break;
							case Hexagrid::TileType::Weapon:
								player->MoveToPosition(tile.indexX, tile.indexY, tile.movementCost);
								grid->ResetFog();
								grid->CalculateVision(tile.indexX, tile.indexY, player->GetViewRange());
								// Parameter tile weapon
								player->EquipWeapon();
								break;
							case Hexagrid::TileType::Enemy:
								if (player->IsWeaponEquiped()) {
									enemy->DamageEnemy(player->GetCurrentWeaponDamage(true));
									grid->ResetSelectedFloor();
									//std::cout << "Clicked on An Enemy With a Weapon" << std::endl;
								}
							default:
								break;
							}
						}
						else {
							player->ShowPlayerSelected(false);
						}
					}
				}
				else {
					player->ShowPlayerSelected(false);
				}
			}

			// Disable after a click so Button pressed is called only once
			buttonReleased = false;
			buttonDown = true;
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && buttonDown == true) {
			buttonReleased = true;
			buttonDown = false;
		}
	}
}

void World::HighlightMouseField() {
	
	sf::Vector2i mousePos = sf::Mouse::getPosition(windowRef);

	if (CheckIfMouseIsInsideTheWindow(mousePos)) {
		grid->HighlightMousePos(mousePos);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			Hexagrid::Tile playerSpawnTile = grid->GetTileRelativeToMouse(mousePos);
			Hexagrid::Tile enemyrSpawnTile = grid->GetRandomTileByType(Hexagrid::TileType::Empty);

			if (playerSpawnTile.isValid)
				player->SpawnPlayer(grid, playerSpawnTile.indexX, playerSpawnTile.indexY);
			else
				player->SpawnPlayer(grid, rand() % 15, rand() % 15);

			enemy->SpawnEnemy(grid, enemyrSpawnTile.indexX, enemyrSpawnTile.indexY, player);
			currentGameState = GameState::PlayerTurn;
		}
	}
}

bool World::CheckIfMouseIsInsideTheWindow(sf::Vector2i mousePos) {
	if ((mousePos.x >= 0 && mousePos.x <= windowRef.getSize().x) &&
		(mousePos.y >= 0 && mousePos.y <= windowRef.getSize().y)) {
		return true;
	}
	return false;
}

void World::draw(sf::RenderWindow &window) {

	// Draw order
	grid->DrawBackgroundShapes(window);
	grid->DrawShapes(window);
	if(drawFog)
		grid->DrawFogShapes(window);
	gameUI->Draw(window);
}
