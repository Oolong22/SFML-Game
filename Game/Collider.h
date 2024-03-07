#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& body);
	~Collider();

	void move(float dx, float dy) { body.move(dx, dy); };

	bool checkCollision(Collider& other, sf::Vector2f& direction, float push);

	sf::Vector2f getPosition() { return body.getPosition(); };
	sf::Vector2f getHalfSize() { return body.getSize() / 2.0f; };

private:
	sf::RectangleShape& body;
};

//test