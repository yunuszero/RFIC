#include <iostream>
#include <sstream>
#include "Player.h"
using namespace std;

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	this->boost = boost;
	this->stamina = staminaMax;
	this->thirsty = thirstyMax;
	
	row = 0;
	maxColumn = 4;
	faceRight = true;

	body.setSize(sf::Vector2f(100.0f, 100.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(0.0f, 50.0f);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	velocity.x = 0.0f;
	speed += 0.005f;
	boost = 0.0f;

	sf::Texture texture;

	sf::Time elapse = this->sec.getElapsedTime();
	if (sectemp != (int)elapse.asSeconds()) {
		//cout << (int)elapse.asSeconds() << endl;
		sectemp = (int)elapse.asSeconds();
		thirsty -= 1.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && stamina > 0) {
			thirsty -= 1.0f;
		}
		if (thirsty < 0) {
			thirsty = 0;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && stamina > 0) {
		boost = speed * 1.0f;
		stamina -= 0.05f;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && stamina < 100) {
		stamina += 0.01f;
	}
	// auto run on x axis.
	velocity.x += (speed + boost);
	
	velocity.y += 981.0f * deltaTime;

	if (velocity.x == 0.0f) 
	{
		if (toggleJump) 
		{
			row = 0;
			maxColumn = 4;
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && stamina > 0){
			if (toggleJump)
			{
				row = 2;
				maxColumn = 8;
			}
		}
		else {
			if (toggleJump)
			{
				row = 1;
				maxColumn = 6;
			}
		}

		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && toggleJump)
	{
		toggleJump = false;
		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
		row = 3;
		maxColumn = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		body.setSize(sf::Vector2f(100.0f, 50.0f));
		body.setOrigin(body.getSize() / 2.0f);
		velocity.y += (speed * 8) * deltaTime;
		row = 5;
		maxColumn = 1;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		body.setSize(sf::Vector2f(100.0f, 100.0f));
		body.setOrigin(body.getSize() / 2.0f);
		if (!toggleJump) row = 3;
	}

	if(row != 0) animation.Update(row, maxColumn, deltaTime*5, faceRight);
	else animation.Update(row, maxColumn, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		velocity.y = 0.0f;
		toggleJump = true;
	}
	else if (direction.y > 0.0f)
	{
		velocity.y = 0.0f;
	}
}

void Player::Stamina(sf::RenderWindow& window, sf::View& view)
{
	staminaBar.setSize(sf::Vector2f(stamina*3, 20.0f));
	staminaBar.setFillColor(sf::Color::Yellow);
	staminaBar.setPosition(view.getCenter().x - (view.getSize().x / 2), view.getCenter().y - (view.getSize().y / 2) + 25);

	sf::Font font;
	if (!font.loadFromFile("res/fonts/consola.ttf"))
	{
		cout << "Can't load file.";
		//return EXIT_FAILURE;
	}
	sf::Text bar;
	bar.setFont(font);
	bar.setCharacterSize(24);
	bar.Bold;
	bar.setFillColor(sf::Color::Black);

	ostringstream ss;
	ss << int(stamina);
	bar.setString(ss.str());
	bar.setPosition(view.getCenter().x - (view.getSize().x / 2), view.getCenter().y - 250.0f);
	window.draw(staminaBar);
	window.draw(bar);
}

void Player::Thirsty(sf::RenderWindow& window, sf::View& view)
{
	thirstyBar.setSize(sf::Vector2f(thirsty * 1.5, 20.0f));
	thirstyBar.setFillColor(sf::Color::Blue);
	thirstyBar.setPosition(view.getCenter().x - (view.getSize().x / 2), view.getCenter().y - (view.getSize().y / 2));

	sf::Font font;
	if (!font.loadFromFile("res/fonts/consola.ttf"))
	{
		cout << "Can't load file.";
		//return EXIT_FAILURE;
	}
	sf::Text bar;
	bar.setFont(font);
	bar.setCharacterSize(24);
	bar.Bold;
	bar.setFillColor(sf::Color::Black);

	ostringstream ss;
	ss << float(thirsty);
	bar.setString(ss.str());
	bar.setPosition(view.getCenter().x - (view.getSize().x / 2), view.getCenter().y - (view.getSize().y / 2) - 6);

	window.draw(thirstyBar);
	window.draw(bar);
}
