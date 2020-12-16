#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setPosition(position);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
}

Platform::~Platform()
{
}

void Platform::move(sf::Vector2f position)
{
	body.setPosition(position);
}

void Platform::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
