#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation()
{

}

void Animation::Update(int row,int maxColumn, float deltaTime, bool faceRight)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (currentImage.x >= maxColumn)
	{
		currentImage.x = 0;
	}

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= maxColumn)
		{
			currentImage.x = 0;
		}
	}

	uvRect.top = currentImage.y * uvRect.height;

	if (faceRight)
	{
		uvRect.left = currentImage.x * abs(uvRect.width);
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}
