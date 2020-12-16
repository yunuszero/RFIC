#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("res/fonts/consola.ttf"))
	{
		//handle error
	}

	menu[0].setFont(font);
	menu[0].setCharacterSize(24);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f((width / 2) - 24, (height / MAX_NUMBER_OF_ITEMS + 1) * 1 +20));

	menu[1].setFont(font);
	menu[1].setCharacterSize(24);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Leaderboard");
	menu[1].setPosition(sf::Vector2f((width / 2) - 70, (height / MAX_NUMBER_OF_ITEMS + 1) * 1.5 +20));

	menu[2].setFont(font);
	menu[2].setCharacterSize(24);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f((width / 2) - 24, (height / MAX_NUMBER_OF_ITEMS + 1) * 2 +20));
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::Moveup()
{
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
