#pragma once
#include<SFML/Graphics.hpp>

class Map
{
public:
	Map(sf::Texture *texture, float x, float y);
	~Map();

	void draw(sf::RenderWindow& window) { window.draw(body); }

private:
	sf::RectangleShape body;
	
};

