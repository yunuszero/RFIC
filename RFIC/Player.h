#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"Collider.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	void Stamina(sf::RenderWindow& window, sf::View& view);
	void Thirsty(sf::RenderWindow& window, sf::View& view);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	bool GetThirsty() { return thirsty; }
	
	/* Setting */
	void setPosition(sf::Vector2f position) { body.setPosition(position); }
	void setThirsty(float thirsty) { this->thirsty = thirsty; }
	void setStamina(float stamina) { this->stamina = stamina; }
	void setSpeed(float speed) { this->speed = speed; }
	/* Add */
	void addThirsty(float n) { this->thirsty += n; }
	void addStamina(float stamina) { this->stamina += stamina; }
	void addSpeed(float speed) { this->speed += speed; }

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	float boost;
	bool faceRight;
	int maxColumn;
	float stamina;
	float thirsty;
	const float staminaMax = 100;
	const float thirstyMax = 200;
	
	sf::Vector2f velocity;
	bool toggleJump;
	float jumpHeight;

	sf::RectangleShape staminaBar;
	sf::RectangleShape thirstyBar;

	sf::Clock sec;
	int sectemp = 0;
};

