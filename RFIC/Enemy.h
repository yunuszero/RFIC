#pragma once
#include<SFML/Graphics.hpp>
#include"Collider.h"
#include"Animation.h"

class Enemy
{
public:
	Enemy(sf::Texture* texture, int r, sf::Vector2u imageCount, int maxColumn, float switchTime, float speed, sf::Vector2f size, sf::Vector2f position);
	~Enemy();

	void Update(float deltaTime);
	void move(sf::Vector2f position) { body.setPosition(position); }
	void Draw(sf::RenderWindow& window) { window.draw(body); }
	int GetItems() { return this->row; }

	Collider GetCollider() { return Collider(body); }
	sf::Vector2f GetPosition() { return body.getPosition(); }

private:
	Animation animation;
	sf::RectangleShape body;
	int row;
	sf::Vector2f velocity;
	int maxColumn;
	float speed;
};

