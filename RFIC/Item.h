#pragma once
#include"SFML/Graphics.hpp"
#include"Animation.h"
#include"Collider.h"

class Item
{
public:
	Item(sf::Texture* texture, int r, sf::Vector2u imageCount, float switchTime, sf::Vector2f size, sf::Vector2f position);
	~Item();
	
	void Update(float deltaTime);
	void move(sf::Vector2f position) { body.setPosition(position); }
	void Draw(sf::RenderWindow& window) { window.draw(body); }
	int GetItems() { return this->row; }

	Collider GetCollider() { return Collider(body); }
	sf::Vector2f GetPosition() { return body.getPosition(); }


private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	int maxColumn = 3;
};

