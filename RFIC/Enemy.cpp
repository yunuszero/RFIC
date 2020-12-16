#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, int r, sf::Vector2u imageCount, int maxColumn, float switchTime, float speed, sf::Vector2f size, sf::Vector2f position):
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->row = r;
	this->maxColumn = maxColumn;
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);

}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	velocity.x -= speed*deltaTime;
	animation.Update(this->row, this->maxColumn, deltaTime, true);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}
