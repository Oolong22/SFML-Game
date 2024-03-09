#include "Coin.h"

Coin::Coin(sf::Texture* texture, sf::Vector2u imageCount, float animationTime, sf::Vector2f position, sf::Vector2f size) :
	animation(texture, imageCount, animationTime / imageCount.x)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
}

Coin::~Coin()
{
}

void Coin::drawTo(sf::RenderWindow& window)
{
	window.draw(body);
}

void Coin::update(float deltaTime) {
	animation.update(0, deltaTime);
	body.setTextureRect(animation.uvRect);
}
