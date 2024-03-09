#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Animation.h"

class Coin
{
public:
	Coin(sf::Texture* texture, sf::Vector2u imageCount, float animationTime, sf::Vector2f position, sf::Vector2f size = sf::Vector2f(32.0f, 32.0f));
	~Coin();

	void drawTo(sf::RenderWindow& window);
	void update(float deltaTime);
	Collider getCollider() { return Collider(body); };

private:
	sf::RectangleShape body;
	Animation animation;
};

