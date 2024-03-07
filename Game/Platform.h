#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Platform
{
public:
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, sf::Color color = sf::Color::White);
	~Platform();

	void drawTo(sf::RenderWindow& window);
	Collider getCollider() { return Collider(body); };

private:
	sf::RectangleShape body;
};

//test