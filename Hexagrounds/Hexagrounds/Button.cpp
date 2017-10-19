#include "Button.h"

Button::Button(int posX, int posY, sf::Texture* texture, Player* player) {
	shape = sf::RectangleShape(sf::Vector2f(100, 100));
	shape.setTexture(texture);
	shape.setPosition(posX, posY);
	this->player = player;
}

void Button::Update(sf::RenderWindow& window) {

	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	if ((mousePos.x < shape.getPosition().x + 101 && mousePos.x > shape.getPosition().x - 1) &&
		(mousePos.y < shape.getPosition().y + 101 && mousePos.y > shape.getPosition().y - 1)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && buttonReleased == true) {

			player->SetSkiptTurn(true);
			//printf("Button was pressed");

			buttonReleased = false;
			buttonDown = true;
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && buttonDown == true) {
			buttonReleased = true;
			buttonDown = false;
		}
	}
}

void Button::OnClicked(sf::RenderWindow& window) {

};

void Button::Draw(sf::RenderWindow& window) {
	window.draw(shape);
};
