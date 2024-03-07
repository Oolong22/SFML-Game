#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	~Player();

	void update(float deltaTime);
	void drawTo(sf::RenderWindow& window);
	void onCollision(sf::Vector2f direction);

	sf::Vector2f getPositon();
	Collider getCollider() { return Collider(body); };

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;

	sf::Vector2f velocity;
	bool canJump = true;
	float jumpHeight;
};

//test