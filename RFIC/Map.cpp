#include<iostream>
#include "Map.h"

Map::Map(sf::Texture *texture, float x, float y)
{
	body.setSize(sf::Vector2f(1920.0f, 1080.0f));
	body.setTexture(texture);
	body.setPosition(sf::Vector2f(x, y));
}

Map::~Map()
{
}
