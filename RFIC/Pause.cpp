#include "Pause.h"

Pause::Pause(float width, float height)
{
	if (!font.loadFromFile("res/fonts/consola.ttf"))
	{
		//handle error
	}

	menu[0].setFont(font);
	menu[0].setCharacterSize(24);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Resume");
	menu[0].setPosition(sf::Vector2f(width - 48, (height)));

	menu[1].setFont(font);
	menu[1].setCharacterSize(24);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Main Menu");
	menu[1].setPosition(sf::Vector2f(width - 68, (height) + 48));
}

Pause::~Pause()
{
}

void Pause::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Pause::Moveup()
{
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Pause::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
