#include "Item.h"

Item::Item(sf::Texture* texture, int r, sf::Vector2u imageCount, float switchTime, sf::Vector2f size, sf::Vector2f position) :
	animation(texture, imageCount, switchTime)
{
	this->row = r;
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

Item::~Item()
{
}

void Item::Update(float deltaTime)
{
	animation.Update(this->row, maxColumn, deltaTime, true);
	body.setTextureRect(animation.uvRect);
}
